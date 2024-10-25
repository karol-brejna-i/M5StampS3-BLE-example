#include <Arduino.h>

#include "BLEControl.h"
#include "LEDController.h"

// UUIDs for the service and characteristic
// #define SERVICE_UUID "12345678-1234-1234-1234-123456789012"
// #define CHARACTERISTIC_UUID "87654321-4321-4321-4321-210987654321"
#define DEVICE_NAME "Bramator"

#define SERVICE_UUID "00001234-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID "00005678-0000-1000-8000-00805F9B34FB"

LEDController ledController;
BLEControl bleControl(DEVICE_NAME, SERVICE_UUID, CHARACTERISTIC_UUID, ledController);

void setup() {
    // initialize serial output for debugging
    USBSerial.begin(115200);
    USBSerial.println("BLE with StampS3 demo!");

    // start the BLE controller
    bleControl.begin();
}

void loop() {
    if (bleControl.isDeviceConnected()) {
        USBSerial.print("+");
    } else {
        USBSerial.print(".");
    }

    delay(1000);
    yield();
}
