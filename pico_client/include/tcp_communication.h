#ifndef TCP_COMMUNICATION_H
#define TCP_COMMUNICATION_H

#include "lwip/err.h"

err_t pico_send_to_thingspeak(const char *api_key, int field_input);

#endif
