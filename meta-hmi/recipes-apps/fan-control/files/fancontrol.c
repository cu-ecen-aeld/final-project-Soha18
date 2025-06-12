#include "fancontrol.h"
#include <stdio.h>
#include <stdlib.h>
#include <gpiod.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>

static struct gpiod_chip *chip = NULL;
static struct gpiod_line_request *request = NULL;
static unsigned int gpio_line_num = 17;  // Changed to GPIO17
static const char *chipname = "/dev/gpiochip0";

#define MANUAL_CTRL_FILE "/tmp/fan_manual_status.txt"  // Fixed filename to match daemon

int fan_init(const char *chip_path, unsigned int gpio_line) {
    struct gpiod_line_settings *settings;
    struct gpiod_line_config *line_cfg;
    struct gpiod_request_config *req_cfg;
    
    // Update global variables with passed parameters
    chipname = chip_path;
    gpio_line_num = gpio_line;
    
    // Open the GPIO chip
    chip = gpiod_chip_open(chipname);
    if (!chip) {
        perror("Open chip failed");
        return -1;
    }
    
    // Create line settings for output with initial value HIGH (fan OFF for active-low)
    settings = gpiod_line_settings_new();
    if (!settings) {
        perror("Failed to create line settings");
        gpiod_chip_close(chip);
        chip = NULL;
        return -1;
    }
    
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
    // For active-low relay: HIGH = OFF, LOW = ON
    // Start with fan OFF (HIGH)
    gpiod_line_settings_set_output_value(settings, GPIOD_LINE_VALUE_ACTIVE);
    
    // Create line configuration
    line_cfg = gpiod_line_config_new();
    if (!line_cfg) {
        perror("Failed to create line config");
        gpiod_line_settings_free(settings);
        gpiod_chip_close(chip);
        chip = NULL;
        return -1;
    }
    
    if (gpiod_line_config_add_line_settings(line_cfg, &gpio_line_num, 1, settings) < 0) {
        perror("Failed to add line settings");
        gpiod_line_config_free(line_cfg);
        gpiod_line_settings_free(settings);
        gpiod_chip_close(chip);
        chip = NULL;
        return -1;
    }
    
    // Create request configuration
    req_cfg = gpiod_request_config_new();
    if (!req_cfg) {
        perror("Failed to create request config");
        gpiod_line_config_free(line_cfg);
        gpiod_line_settings_free(settings);
        gpiod_chip_close(chip);
        chip = NULL;
        return -1;
    }
    
    gpiod_request_config_set_consumer(req_cfg, "fancontrol");
    
    // Request the line
    request = gpiod_chip_request_lines(chip, req_cfg, line_cfg);
    if (!request) {
        perror("Request line as output failed");
        gpiod_request_config_free(req_cfg);
        gpiod_line_config_free(line_cfg);
        gpiod_line_settings_free(settings);
        gpiod_chip_close(chip);
        chip = NULL;
        return -1;
    }
    
    // Clean up configuration objects
    gpiod_request_config_free(req_cfg);
    gpiod_line_config_free(line_cfg);
    gpiod_line_settings_free(settings);
    
    openlog("fancontrol", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Fan Initialized on GPIO %u (active-low relay)", gpio_line_num);
    return 0;
}

int fan_on(void) {
    if (!request) return -1;
    
    // Active-low relay: set GPIO LOW (0) to turn fan ON
    if (gpiod_line_request_set_value(request, gpio_line_num, GPIOD_LINE_VALUE_INACTIVE) < 0) {
        syslog(LOG_ERR, "Failed to turn fan ON (%s)", strerror(errno));
        return -1;
    }
    syslog(LOG_INFO, "Fan turned ON (GPIO%u = LOW)", gpio_line_num);
    return 0;
}

int fan_off(void) {
    if (!request) return -1;
    
    // Active-low relay: set GPIO HIGH (1) to turn fan OFF
    if (gpiod_line_request_set_value(request, gpio_line_num, GPIOD_LINE_VALUE_ACTIVE) < 0) {
        syslog(LOG_ERR, "Failed to turn fan OFF (%s)", strerror(errno));
        return -1;
    }
    syslog(LOG_INFO, "Fan turned OFF (GPIO%u = HIGH)", gpio_line_num);
    return 0;
}

// Fixed to match daemon's expected filename
int set_manual_override(int state) {
    FILE *fp = fopen(MANUAL_CTRL_FILE, "w");
    if (!fp) {
        syslog(LOG_ERR, "Failed to write manual override");
        return -1;
    }
    fprintf(fp, "%s\n", state ? "on" : "off");  // Write "on"/"off" instead of "1"/"0"
    fclose(fp);
    return 0;
}

int get_manual_override(int *state) {
    FILE *fp = fopen(MANUAL_CTRL_FILE, "r");
    if (!fp) {
        *state = 0;  // Default to off if file doesn't exist
        return 0;
    }
    
    char status[10];
    if (fscanf(fp, "%9s", status) == 1) {
        *state = (strcmp(status, "on") == 0) ? 1 : 0;
    } else {
        *state = 0;
    }
    fclose(fp);
    return 0;
}

// Add the read_temperature function to match header
float read_temperature(void) {
    float temperature = 0.0;
    FILE *fp = fopen("/tmp/bme280_values.txt", "r");
    if (fp) {
        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            // Keep reading until the last line
        }
        // Now 'line' holds the last line in the file
        if (sscanf(line, "Temp: %f", &temperature) != 1) {
            temperature = 0.0;  // Default on parse error
        }
        fclose(fp);
    }
    return temperature;
}

void fan_release(void) {
    if (request) {
        // Turn OFF before release (active-low: set to HIGH)
        gpiod_line_request_set_value(request, gpio_line_num, GPIOD_LINE_VALUE_ACTIVE);
        gpiod_line_request_release(request);
        request = NULL;
    }
    if (chip) {
        gpiod_chip_close(chip);
        chip = NULL;
    }
    syslog(LOG_INFO, "Fan released (GPIO%u set HIGH)", gpio_line_num);
    closelog();
}
