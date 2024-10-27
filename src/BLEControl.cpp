#include "BLEControl.h"

BLEControl::BLEControl(const char* deviceName, const char* serviceUUID, const char* characteristicUUID,
                       LEDController& ledController)
    : _deviceName(deviceName),
      _serviceUUID(serviceUUID),
      _characteristicUUID(characteristicUUID),
      _ledController(ledController) {}

void BLEControl::begin() {
    USBSerial.println("blecontrol begin");
    // Initialize BLE
    BLEDevice::init(_deviceName);
    _pServer = BLEDevice::createServer();
    _pServer->setCallbacks(new MyServerCallbacks(this));

    // Create BLE service
    BLEService* pService = _pServer->createService(_serviceUUID);

    // Create BLE characteristic
    _pCharacteristic = pService->createCharacteristic(_characteristicUUID, BLECharacteristic::PROPERTY_WRITE);
    _pCharacteristic->setCallbacks(new MyCharacteristicCallbacks(this));

    // Start the service
    pService->start();

    // Start advertising the BLE service
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(_serviceUUID);

    // TODO: try more "sophisticated" advertising
    // take a look at
    // https://github.com/espressif/arduino-esp32/blob/74e4a744ce0bae127cd2eeac04e62c2bf45a9c93/libraries/BLE/examples/BLE5_periodic_advertising/BLE5_periodic_advertising.ino

    pAdvertising->setScanResponse(false);
    // see:
    // https://github.com/espressif/esp-idf/blob/v5.2.3/examples/bluetooth/bluedroid/ble/gatt_server/tutorial/Gatt_Server_Example_Walkthrough.md
    pAdvertising->setMinPreferred(0x20);  // 0x20 * 0.625ms = 32 * 0.625ms = 20ms;
    pAdvertising->setMaxPreferred(0x40);
    BLEDevice::startAdvertising();
}

bool BLEControl::isDeviceConnected() { return _deviceConnected; }

void BLEControl::MyServerCallbacks::onConnect(BLEServer* pServer) { _bleControl->_deviceConnected = true; }

void BLEControl::MyServerCallbacks::onDisconnect(BLEServer* pServer) {
    _bleControl->_deviceConnected = false;
    pServer->startAdvertising();  // restart advertising
}

void BLEControl::MyCharacteristicCallbacks::onWrite(BLECharacteristic* pCharacteristic) {
    USBSerial.println("onWrite triggered");
 
    std::string value = pCharacteristic->getValue();
    
    if (!value.empty()) {
        int result = _bleControl->_ledController.consumeInput(value);
        if (result > 0) {
            _bleControl->_ledController.update();
        } else if (result == 0) {
            USBSerial.println("LED state not changed.");
        } else {
            USBSerial.println("Setting LEDstate failed.");
        }
    } else {
        USBSerial.println("Received empty value");
    }
}
