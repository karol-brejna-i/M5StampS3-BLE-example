
#include "LEDController.h"

#include <Arduino.h>
#include <FastLED.h>

LEDController::LEDController() : _led_status(0) { FastLED.addLeds<WS2812, PIN_LED, GRB>(_leds, NUM_LEDS); }

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

int LEDController::consumeInput(const std::string& value) {
    try {
        // Convert string to integer
        int intValue = std::stoi(value);
        USBSerial.print("Converted intValue: ");
        USBSerial.println(intValue);

        // Attempt to set the LED status and return the result
        return setLedStatus(static_cast<uint8_t>(intValue));

    } catch (const std::invalid_argument& e) {
        USBSerial.println("Invalid argument in consumeInput");
        return -1;  // Error during conversion
    } catch (const std::out_of_range& e) {
        USBSerial.println("Out of range in consumeInput");
        return -1;  // Error during conversion
    }
}

// Change the LED status manually
int LEDController::setLedStatus(uint8_t status) {
    if (status == _led_status) {
        return 0;  // State has not changed
    }
    if (status <= 3) {  // Only need to check the upper bound since status is uint8_t
        _led_status = status;
        return 1;  // State has changed
    }
    return -1;  // Invalid status
}

// Get the current LED status as a string
String LEDController::getLedStatusString() const { return _led_status_string[_led_status]; }

// Get the current LED status as an integer
uint8_t LEDController::getLedStatus() const { return _led_status; }
