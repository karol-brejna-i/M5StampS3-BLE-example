
#include "LEDController.h"

#include <Arduino.h>
#include <FastLED.h>

LEDController::LEDController() : _led_status(0) {
    FastLED.addLeds<WS2812, PIN_LED, GRB>(_leds, NUM_LEDS);
}

// Initialize the LED controller
void LEDController::begin() {}

// Update the LED state
void LEDController::update() {
    // Update the LED color based on the current status
    switch (_led_status) {
        case 0:  // Off
            _leds[0] = CRGB::Black;
            break;
        case 1:  // Red
            _leds[0] = CRGB::Red;
            break;
        case 2:  // Green
            _leds[0] = CRGB::Green;
            break;
        case 3:  // Blue
            _leds[0] = CRGB::Blue;
            break;
        default:
            _leds[0] = CRGB::Black;  // Default to off for safety
            break;
    }

    FastLED.show();
}

// Change the LED status manually
void LEDController::setLedStatus(uint8_t status) {
    if (status <= 3) {         // Limit status to valid values (0 to 3)
        _led_status = status;
    }
}

// Get the current LED status as a string
String LEDController::getLedStatusString() const { return _led_status_string[_led_status]; }

// Get the current LED status as an integer
uint8_t LEDController::getLedStatus() const { return _led_status; }
