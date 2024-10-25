#include "BLEControl.h"

BLEControl::BLEControl(const char* deviceName, const char* serviceUUID, const char* characteristicUUID,
                       LEDController& ledController)
    : _deviceName(deviceName),
      _serviceUUID(serviceUUID),
      _characteristicUUID(characteristicUUID),
      _ledController(ledController) {
    USBSerial.println("blecontrol constructioe");
}

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

    // // xxx todo  experimental:
    // BLEAdvertisementData advertisementData;
    // advertisementData.setName(_deviceName);  // Add device name to advertising
    // advertisementData.setShortName("dupa");
    // advertisementData.setManufacturerData("kulci crew");
    // USBSerial.println("add data:");
    // USBSerial.println(advertisementData.getPayload().c_str());
    // pAdvertising->setAdvertisementData(advertisementData);
    // pAdvertising->setScanResponse(true); // was (false);
    // // xxx end of experimental

    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x06);  // Helps with iPhone connection issue // XXX what is this shit?
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
}

bool BLEControl::isDeviceConnected() { return _deviceConnected; }

void BLEControl::MyServerCallbacks::onConnect(BLEServer* pServer) { _bleControl->_deviceConnected = true; }

void BLEControl::MyServerCallbacks::onDisconnect(BLEServer* pServer) {
    _bleControl->_deviceConnected = false;
    pServer->startAdvertising();  // restart advertising
}
void BLEControl::MyCharacteristicCallbacks::onWrite(BLECharacteristic* pCharacteristic) {
    std::string value = pCharacteristic->getValue();

    USBSerial.println("callback");
    USBSerial.println(value.c_str());
    if (value.length() > 0) {
        USBSerial.print("length > 0 ");
        try {
            // Convert string to integer
            int intValue = std::stoi(value);
            USBSerial.println(intValue);
            intValue = static_cast<uint8_t>(intValue);
            USBSerial.print("intValue: ");
            USBSerial.println(intValue);

            // XXX TODO: I don't believe BLE Control should now what are the allowed states; let us ledController
            // decide on this. Check if the integer is in the desired range (0 to 4)
            if (intValue >= 0 && intValue <= 4) {
            } else {
                intValue = 0;
            }

            _bleControl->_ledController.setLedStatus(intValue);
            _bleControl->_ledController.update();

            // _ledController->setLedStatus(intValue);
        } catch (const std::invalid_argument& e) {
            // XXX TODO: notify about the error
            USBSerial.println("exception");
            USBSerial.println("dupa 1");
        } catch (const std::out_of_range& e) {
            // XXX TODO: notify about the error
            USBSerial.println("exception");
            USBSerial.println("dupa 2");
        }

        // // If the received value is "1", turn the LED on
        // if (value == "1") {
        //     // digitalWrite(_bleControl->_ledPin, HIGH);
        //     _bleControl->_ledState = true;
        // }
        // // If the received value is "0", turn the LED off
        // else if (value == "0") {
        //     // digitalWrite(_bleControl->_ledPin, LOW);
        //     _bleControl->_ledState = false;
        // }
    } else {
        USBSerial.println("length <= 0");
    }
}
