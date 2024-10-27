#include <Arduino.h>

#include "BLEController.h"
#include "LEDController.h"


#define DEVICE_NAME "Bramator"

#define SERVICE_UUID "00001234-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID "00005678-0000-1000-8000-00805F9B34FB"

LEDController ledController;
BLEController BLEController(DEVICE_NAME, SERVICE_UUID, CHARACTERISTIC_UUID, ledController);

void setup() {
    // initialize serial output for debugging
    USBSerial.begin(115200);
    USBSerial.println("BLE with StampS3 demo!");

    // start the BLE controller
    BLEController.begin();
}

void loop() {
    if (BLEController.isDeviceConnected()) {
        USBSerial.print("+");
    } else {
        USBSerial.print(".");
    }

    delay(1000);
    yield();
}
