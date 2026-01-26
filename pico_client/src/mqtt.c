#include "../include/mqtt.h"

static void mqtt_incoming_data_callback(void* argument,
					const u8_t* data,
                                  	u16_t length,
					u8_t flags)
{
    printf("[+] MQTT RX: %.*s\n", length, (const char*)data);
}

static void mqtt_incoming_publish_callback(void* argument,
                                     	   const char* topic, 
					   u32_t total_length) 
{
    printf("[+] Topic: %s . . .\n", topic);
}

static void mqtt_connection_callback(mqtt_client_t* client,
			             void* argument,
                                     mqtt_connection_status_t status) 
{
    if (status != MQTT_CONNECT_ACCEPTED) 
    {
        printf("[-] MQTT connect failed: %d . . .\n", status);
        return;
    }

    printf("[+] MQTT connected to ThingSpeak . . .\n");
    
    const char* message = "field1=25.5&status=Pico W online";
    mqtt_publish(client, 
		 PUBLISH_TOPIC, 
		 message, strlen(message), 
		 0, 0, 
		 NULL, NULL);
}

static void mqtt_init(void)
{
    client = mqtt_client_new();

    mqtt_set_inpub_callback(client,
		    	    mqtt_incoming_publish_callback,
			    mqtt_incoming_data_callback,
			    NULL);

    ip_addr_t broker_address;
    ipaddr_aton(MQTT_BROKER_ADDRESS, &broker_address);

    struct mqtt_connect_client_info_t connectOptions = {
	    .client_id = MQTT_THINGSPEAK_CLIENT_ID,
	    .client_user = MQTT_THINGSPEAK_CLIENT_ID,
	    .client_pass = MQTT_THINGSPEAK_API_KEY,
	    .keep_alive = 60,
	    .will_topic = NULL,
	    .will_msg = NULL,
	    .will_qos = 0,
	    .will_retain = 0
    };

    mqtt_client_connect(client, 
		        &broker_address,
			MQTT_BROKER_PORT,
			mqtt_connection_callback,
			NULL, &connectOptions);
}
