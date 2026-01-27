#include "wifi.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int wifi_init(void) {
	if (cyw43_arch_init()){
		printf("Wi-Fi init misslyckades\n");
		return -1;
	}

	cyw43_arch_enable_sta_mode();

	if (cyw43_arch_wifi_connect_timeout_ms("JENSEN-Guest", "pwd", CYW43_AUTH_WPA2_AES_PSK, 40000)){
		printf("Anslutning misslyckades\n");
		return -1;
	} else {
		printf("Ansluten!\n");
		return 0;
	}
}
