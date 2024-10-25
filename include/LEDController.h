#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>
#include <FastLED.h>

// Define the number of LEDs and the pin
#define NUM_LEDS 1
#define PIN_LED 21  // Define the LED pin as a constant

class LEDController {
   public:
    // Constructor
    LEDController();

    // Initialize the LED controller
    void begin();

    // Update the LED state
    void update();

    // Change the LED status manually
    void setLedStatus(uint8_t status);

    // Get the current LED status as a string
    String getLedStatusString() const;

    // Get the current LED status as an integer
    uint8_t getLedStatus() const;

   private:
    uint8_t _led_status;
    CRGB _leds[NUM_LEDS];
    String _led_status_string[4] = {"Off", "Red", "Green", "Blue"};  // Updated to reflect 0-3 range
};

#endif  // LEDCONTROLLER_H
