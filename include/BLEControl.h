#ifndef BLE_CONTROL_H
#define BLE_CONTROL_H

#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "LEDController.h"  // Include the LEDController header

class BLEControl {
   public:
    // Modify the constructor to take a reference to LEDController
    BLEControl(const char* deviceName, const char* serviceUUID, const char* characteristicUUID,
               LEDController& ledController);

    void begin();
    bool isDeviceConnected();

   private:
    const char* _deviceName;
    const char* _serviceUUID;
    const char* _characteristicUUID;

    BLEServer* _pServer = NULL;
    BLECharacteristic* _pCharacteristic = NULL;
    bool _deviceConnected = false;
    bool _ledState = false;
    LEDController& _ledController;  // Reference to the LEDController object

    class MyServerCallbacks : public BLEServerCallbacks {
       public:
        MyServerCallbacks(BLEControl* bleControl) : _bleControl(bleControl) {}
        void onConnect(BLEServer* pServer) override;
        void onDisconnect(BLEServer* pServer) override;

       private:
        BLEControl* _bleControl;
    };

    class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
       public:
        MyCharacteristicCallbacks(BLEControl* bleControl) : _bleControl(bleControl) {}
        void onWrite(BLECharacteristic* pCharacteristic) override;

       private:
        BLEControl* _bleControl;
    };

    friend class MyServerCallbacks;
    friend class MyCharacteristicCallbacks;
};

#endif
