#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>
#include <FastLED.h>

// Define the number of LEDs and the pin
#define NUM_LEDS 1
#define PIN_LED 21  // Define the LED pin as a constant

/**
 * @class LEDController
 * @brief Controls the LED status, allowing initialization, updates, and state changes.
 */
class LEDController {
   public:
    /**
     * @brief Constructs a new LEDController object with default settings.
     */
    LEDController();

    /**
     * @brief Initializes the LED controller hardware and prepares it for operation.
     *
     * This method should be called once during setup to initialize any resources
     * required for LED control.
     */
    void begin();

    /**
     * @brief Updates the LED state to reflect the current status.
     *
     * This method should be called repeatedly in the main loop to ensure that
     * the LED displays the correct color or state.
     */
    void update();

    /**
     * @brief Sets the LED status to the specified value.
     *
     * @param status Integer value representing the LED state (0-3).
     * @return int Returns:
     * - 1 if the status changed,
     * - 0 if the status was already set to the specified value,
     * - -1 if the input status is out of the valid range.
     */
    int setLedStatus(uint8_t status);

    /**
     * @brief Parses a string input to set the LED status.
     *
     * Converts the string to an integer and attempts to set the LED status based
     * on the converted value.
     *
     * @param value String input representing the LED status.
     * @return int Returns:
     * - 1 if the status changed,
     * - 0 if the status was unchanged,
     * - -1 if there was an error (invalid input or out-of-range).
     */
    int consumeInput(const std::string& value);

    /**
     * @brief Retrieves the current LED status as a descriptive string.
     *
     * @return String Current LED status (e.g., "Off", "Red").
     */
    String getLedStatusString() const;

    /**
     * @brief Retrieves the current LED status as an integer.
     *
     * @return uint8_t Integer representation of the LED status (0-3).
     */
    uint8_t getLedStatus() const;

   private:
    uint8_t _led_status;                                             ///< Current LED status (0-3).
    CRGB _leds[NUM_LEDS];                                            ///< Array of LED states and colors.
    String _led_status_string[4] = {"Off", "Red", "Green", "Blue"};  ///< Descriptive labels for LED status.
};

#endif  // LEDCONTROLLER_H
