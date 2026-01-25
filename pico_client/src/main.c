#include "wifi.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "lcd.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

// --- FUNCTION PROTOTYPES ---
// We declare these here, but implement them later or in other files
void init_system(void);
int read_buttons(void);
void send_to_thingspeak(int rating);
void update_lcd(int rating);

int main() {
    init_system(); // Starts buttons, WiFi, LCD

    // "Main control loop"
    while(1) {
        // 1. Check which button is pressed (returns 0 if none, otherwise 1-5)
        int rating = read_buttons();

        // If we actually got a rating (someone pressed a button)
        if (rating > 0) {
            printf("Rating registered: %d\n", rating);

             // 2. Send rating to database/ThingSpeak
            send_to_thingspeak(rating);

             // 3. Update status on LCD Screen
            update_lcd(rating);
            
             // Debounce delay to avoid registering the same press multiple times
            sleep_ms(1000); 

        }
        
        sleep_ms(50); // Save power/CPU cycles
    }
    return 0;
}

// --- IMPLEMENTATION DETAILS BELOW ---
// (Your team members will fill these in)

int read_buttons() {
    // Here we place the loop that checks GPIO pins
    // Return integer 1-5 if a button is pressed, otherwise 0
    return 0; // Placeholder
}

void send_to_thingspeak(int rating) {
    // WiFi code goes here
}

void update_lcd(int rating) {
    // LCD code goes here
}

void init_system() {
    // Här lägger vi gpio_init osv.
    stdio_init_all();

    wifi_init();
}
