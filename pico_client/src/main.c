#include <stdio.h>
#include "pico/stdlib.h"


// Vi deklarerar dessa här uppe, men fyller dem med innehåll senare eller i en annan fil
void initiera_allt();
int las_av_knappar();
void skicka_till_thingspeak(int betyg);
void uppdatera_lcd(int betyg);


int main() {
    initiera_allt(); // Startar knappar, wifi, lcd

    // "kontroll-loop"
    while(1) {
        // 1. Titta vilken knapp som trycks (returnerar 0 om ingen trycks, annars 1-5)
        int betyg = las_av_knappar();

        // Om vi faktiskt fick ett betyg (någon tryckte)
        if (betyg > 0) {
             printf("Betyg registrerat: %d\n", betyg);

             // 2. Skicka knapp-färg till databas/thinksspeak
             skicka_till_thingspeak(betyg);

             // 3. Uppdatera status på LCD-Skärm
             uppdatera_lcd(betyg);
             
             // Vänta lite så vi inte registrerar samma tryck flera gånger
             sleep_ms(1000); 
        }
        
        sleep_ms(50); // Sparar ström
    }
    return 0;
}

// --- HÄR UNDER KAN DU SEDAN FYLLA PÅ MED DETALJERNA ---

int las_av_knappar() {
    // Här lägger vi for-loopen som kollar GPIO-pinnarna
    // Returnera siffran 1-5 om en knapp trycks, annars 0
    return 0; // Placeholder
}

void skicka_till_thingspeak(int betyg) {
    // Här lägger vi WiFi-koden
}

void uppdatera_lcd(int betyg) {
    // Här lägger vi LCD-koden
}

void initiera_allt() {
    stdio_init_all();
    // Här lägger vi gpio_init osv.
}