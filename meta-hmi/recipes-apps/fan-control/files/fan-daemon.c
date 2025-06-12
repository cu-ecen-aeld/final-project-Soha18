#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fancontrol.h"
#include <gpiod.h>

#define TEMP_FILE               "/tmp/bme280_values.txt"
#define MODE_FILE               "/tmp/fan_mode.txt"
#define MANUAL_STATUS_FILE      "/tmp/fan_manual_status.txt"
#define FAN_GPIO_LINE           17    // Changed to GPIO17
#define TEMP_THRESHOLD          24.0

void read_mode(char *mode) {
    FILE *fp = fopen(MODE_FILE, "r");
    if (fp) {
        if (fscanf(fp, "%9s", mode) != 1) {  // Prevent buffer overflow
            strcpy(mode, "auto");
        }
        fclose(fp);
    } else {
        strcpy(mode, "auto");  // default if missing
    }
}

void read_manual_status(char *status) {
    FILE *fp = fopen(MANUAL_STATUS_FILE, "r");
    if (fp) {
        if (fscanf(fp, "%9s", status) != 1) {  // Prevent buffer overflow
            strcpy(status, "off");
        }
        fclose(fp);
    } else {
        strcpy(status, "off");  // default if missing
    }
}

int main() {
    if (fan_init("/dev/gpiochip0", FAN_GPIO_LINE) != 0) {
        fprintf(stderr, "Failed to initialize fan GPIO%d\n", FAN_GPIO_LINE);
        return -1;
    }

    char mode[10];
    char manual_status[10];
    float temperature;
    int fan_state = 0;  // 0: off, 1: on

    printf("Fan control system started on GPIO%d (active-low relay)\n", FAN_GPIO_LINE);

    while (1) {
        // Always read temperature (as per requirement)
        temperature = read_temperature();
        
        read_mode(mode);

        if (strcmp(mode, "auto") == 0) {
            // Auto control based on temperature
            if (temperature >= TEMP_THRESHOLD && !fan_state) {
                if (fan_on() == 0) {
                    fan_state = 1;
                    printf("[AUTO] Temp: %.2f°C — Fan ON (GPIO%d=LOW)\n", temperature, FAN_GPIO_LINE);
                } else {
                    printf("[ERROR] Failed to turn fan ON\n");
                }
            } else if (temperature < TEMP_THRESHOLD && fan_state) {
                if (fan_off() == 0) {
                    fan_state = 0;
                    printf("[AUTO] Temp: %.2f°C — Fan OFF (GPIO%d=HIGH)\n", temperature, FAN_GPIO_LINE);
                } else {
                    printf("[ERROR] Failed to turn fan OFF\n");
                }
            }
        } else if (strcmp(mode, "manual") == 0) {
            // Manual control based on GUI button
            read_manual_status(manual_status);
            if (strcmp(manual_status, "on") == 0 && !fan_state) {
                if (fan_on() == 0) {
                    fan_state = 1;
                    printf("[MANUAL] Button ON — Fan ON (GPIO%d=LOW, Temp: %.2f°C)\n", FAN_GPIO_LINE, temperature);
                } else {
                    printf("[ERROR] Failed to turn fan ON\n");
                }
            } else if (strcmp(manual_status, "off") == 0 && fan_state) {
                if (fan_off() == 0) {
                    fan_state = 0;
                    printf("[MANUAL] Button OFF — Fan OFF (GPIO%d=HIGH, Temp: %.2f°C)\n", FAN_GPIO_LINE, temperature);
                } else {
                    printf("[ERROR] Failed to turn fan OFF\n");
                }
            }
        }

        sleep(1);
    }

    fan_release();
    return 0;
}
