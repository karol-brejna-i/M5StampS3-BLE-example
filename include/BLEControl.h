#ifndef BLE_CONTROL_H
#define BLE_CONTROL_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include "LEDController.h"  // Include the LEDController header

/**
 * @class BLEControl
 * @brief Handles BLE functionality including device setup, advertising, and characteristic interactions.
 */
class BLEControl {
   public:
    /**
     * @brief Constructs a BLEControl object with the specified parameters.
     * 
     * @param deviceName Name of the BLE device.
     * @param serviceUUID UUID of the BLE service.
     * @param characteristicUUID UUID of the BLE characteristic.
     * @param ledController Reference to the LEDController object used to manage LED states.
     */
    BLEControl(const char* deviceName, const char* serviceUUID, const char* characteristicUUID,
               LEDController& ledController);

    /**
     * @brief Initializes BLE settings, creates server and services, and starts advertising.
     * 
     * This method must be called to set up the BLE service and make the device
     * discoverable to other BLE clients.
     */
    void begin();

    /**
     * @brief Checks if the BLE device is currently connected to a client.
     * 
     * @return true if connected, false otherwise.
     */
    bool isDeviceConnected();

   private:
    const char* _deviceName;                 ///< Name of the BLE device.
    const char* _serviceUUID;                ///< UUID of the BLE service.
    const char* _characteristicUUID;         ///< UUID of the BLE characteristic.

    BLEServer* _pServer = NULL;              ///< Pointer to the BLE server.
    BLECharacteristic* _pCharacteristic = NULL; ///< Pointer to the BLE characteristic.
    bool _deviceConnected = false;           ///< Connection status of the device.
    LEDController& _ledController;           ///< Reference to the LEDController object.

    /**
     * @class MyServerCallbacks
     * @brief Callback class for handling server connection and disconnection events.
     */
    class MyServerCallbacks : public BLEServerCallbacks {
       public:
        /**
         * @brief Constructs a MyServerCallbacks object.
         * 
         * @param bleControl Pointer to the BLEControl object.
         */
        MyServerCallbacks(BLEControl* bleControl) : _bleControl(bleControl) {}

        /**
         * @brief Callback invoked when a client connects to the BLE server.
         * 
         * @param pServer Pointer to the BLEServer object.
         */
        void onConnect(BLEServer* pServer) override;

        /**
         * @brief Callback invoked when a client disconnects from the BLE server.
         * 
         * @param pServer Pointer to the BLEServer object.
         */
        void onDisconnect(BLEServer* pServer) override;

       private:
        BLEControl* _bleControl;  ///< Pointer to the BLEControl object.
    };

    /**
     * @class MyCharacteristicCallbacks
     * @brief Callback class for handling characteristic write events.
     */
    class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
       public:
        /**
         * @brief Constructs a MyCharacteristicCallbacks object.
         * 
         * @param bleControl Pointer to the BLEControl object.
         */
        MyCharacteristicCallbacks(BLEControl* bleControl) : _bleControl(bleControl) {}

        /**
         * @brief Callback invoked when a value is written to the BLE characteristic.
         * 
         * @param pCharacteristic Pointer to the BLECharacteristic object that received the write.
         */
        void onWrite(BLECharacteristic* pCharacteristic) override;

       private:
        BLEControl* _bleControl;  ///< Pointer to the BLEControl object.
    };

    friend class MyServerCallbacks;          ///< Grant MyServerCallbacks access to private members.
    friend class MyCharacteristicCallbacks;   ///< Grant MyCharacteristicCallbacks access to private members.
};

#endif
