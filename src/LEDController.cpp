
#include "LEDController.h"

LEDController::LEDController() : _led_status(0) { FastLED.addLeds<WS2812, PIN_LED, GRB>(_leds, NUM_LEDS); }

// Initialize the LED controller
void LEDController::begin() {}

// Update the LED state
void LEDController::update() {
    // Array to map LED status to corresponding colors
    const CRGB colors[] = {CRGB::Black, CRGB::Red, CRGB::Green, CRGB::Blue};

    // Set the LED color based on the current status, defaulting to Black (off) if status is out of range
    if (_led_status >= 0 && _led_status < sizeof(colors) / sizeof(colors[0])) {
        _leds[0] = colors[_led_status];
    } else {
        _leds[0] = CRGB::Black;  // Default to off for safety
    }

    FastLED.show();
}

// Parses a string input to set the LED status.
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
        return -1;
    } catch (const std::out_of_range& e) {
        USBSerial.println("Out of range in consumeInput");
        return -1;
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
