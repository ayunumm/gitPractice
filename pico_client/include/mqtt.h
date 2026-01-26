#ifndef MQTT_H
#define MQTT_H

#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/apps/mqtt.h"
#include "lwip/dns.h"

#include "secrets.h"

#define MQTT_BROKER_ADDRESS "mqtt3.thingspeak.com"
#define MQTT_BROKER_PORT 1883

#define PUBLISH_TOPIC "channels/" MQTT_THINGSPEAK_CHANNEL_ID "/publish"
#define SUBSCRIBE_TOPIC "channels/" MQTT_THINGSPEAK_CHANNEL_ID "/subscribe"

static mqtt_client_t* client;

static void mqtt_incoming_data_callback(void* argument, 
					const u8_t* data,
					u16_t length,
					u8_t flags);

static void mqtt_incoming_publish_callback(void* argument,
					   const char* topic,
					   u32_t total_length);

static void mqtt_connection_callback(mqtt_client_t* client,
				     void* argument,
				     mqtt_connection_status_t status);

static void mqtt_init(void);

#endif // MQTT_H
