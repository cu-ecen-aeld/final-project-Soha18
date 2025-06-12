/**
 * @file fancontrol.h
 * @brief Fan control shared library for Embedded Linux systems.
 *
 * This library provides APIs for controlling a GPIO-connected fan
 * via relay, reading sensor temperature from a log file, and handling
 * manual control state.
 *
 * @author Soha
 * @version 1.0
 * @date 2025-05-30
 */

#ifndef FANCONTROL_H
#define FANCONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the fan control system.
 * Must be called before using other APIs.
 * @param chip_path GPIO chip device path (e.g. "/dev/gpiochip0")
 * @param gpio_line GPIO line offset number (e.g. 26)
 * @return 0 on success, negative on error.
 */
int fan_init(const char *chip_path, unsigned int gpio_line);

/**
 * Turn on the fan.
 * @return 0 on success, negative on error.
 */
int fan_on(void);

/**
 * Turn off the fan.
 * @return 0 on success, negative on error.
 */
int fan_off(void);

/**
 * Read the current temperature value from log file.
 * @param[out] temperature Pointer to store the temperature value.
 * @return 0 on success, negative on error.
 */
float read_temperature(void);

/**
 * Set manual override state.
 * @param state 0 = disabled, 1 = enabled
 * @return 0 on success, negative on error.
 */
int set_manual_override(int state);

/**
 * Get manual override state.
 * @param[out] state Pointer to store the state.
 * @return 0 on success, negative on error.
 */
int get_manual_override(int *state);

/**
 * Release resources and close GPIO chip.
 */
void fan_release(void);

#ifdef __cplusplus
}
#endif

#endif // FANCONTROL_H

