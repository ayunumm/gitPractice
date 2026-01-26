#include "tcp_communication.h"

#include "lwip/tcp.h"

#include <string.h>
#include <stdio.h>

#define THINGSPEAK_PORT 80
#define THINGSPEAK_IP "184.106.153.149"

static err_t recv_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
  if (!p) {
    tcp_close(tpcb);
    return ERR_OK;
  }

  if (err != ERR_OK) {
    printf("recv_cb error: %d\n", err);
    printf("Received %d bytes\n", p->len);
    printf("%.*s\n", p->len, (char *)p->payload);
  }

  tcp_recved(tpcb, p->len);
  pbuf_free(p);
  return ERR_OK;
}

static err_t connect_cb(void *arg, struct tcp_pcb *tpcb, err_t err) {
  if (err != ERR_OK) return err;

  const char *request = (const char*)arg;

  tcp_write(tpcb, request, strlen(request), TCP_WRITE_FLAG_COPY);
  tcp_output(tpcb);

  return ERR_OK;
}

err_t pico_send_to_thingspeak(const char *api_key, int field_input) {
  static char request[256];

  snprintf(request, sizeof(request),
    "GET /update?api_key=%s&field1=%d HTTP/1.1\r\n"
    "Host: api.thingspeak.com\r\n"
    "Connection: close\r\n"
    "\r\n",
    api_key,
    field_input
  );

  struct tcp_pcb *pcb = tcp_new();
  if (!pcb) return ERR_MEM;

  tcp_arg(pcb, request);
  tcp_recv(pcb, recv_cb);

  ip_addr_t ip;
  ipaddr_aton(THINGSPEAK_IP, &ip);

  return tcp_connect(pcb, &ip, THINGSPEAK_PORT, connect_cb);
}
