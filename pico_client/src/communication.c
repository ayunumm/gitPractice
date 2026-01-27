#include "communication.h"

#include "lwip/altcp.h"
#include "lwip/altcp_tcp.h"
#include "lwip/dns.h"
#include "lwip/pbuf.h"

static err_t tcp_client_connected(void* arg, struct altcp_pcb* pcb, err_t error)
{
    if (error != ERR_OK) 
    {
        printf("[-] Connection failed: %d . . .\n", error);
        return error;
    }

    printf("[+] Connected to ThingSpeak . . .\n");
    return ERR_OK;
}

static err_t tcp_client_sent(void* arg, struct altcp_pcb* pcb, u16_t len) 
{
    printf("[+] Data sent: %u bytes . . .\n", len);
    return ERR_OK;
}

static err_t tcp_client_recv(void* arg, struct altcp_pcb* pcb, struct pbuf* buffer, err_t error) 
{
    http_request_t* request = (http_request_t*)arg;
    
    if (!buffer) 
    {
        printf("[/] Connection closed . . .\n");
        request->complete = true;
        altcp_close(pcb);
        return ERR_OK;
    }

    if (buffer->tot_len > 0) 
    {
        printf("[+] Received %d bytes: ", buffer->tot_len);
        for (struct pbuf* data = buffer; data != NULL; data = data->next) 
	    {
            printf("%.*s", data->len, (char *)data->payload);
        }
        printf("\n");
    }

    altcp_recved(pcb, buffer->tot_len);
    pbuf_free(buffer);
    
    return ERR_OK;
}

bool send_to_thingspeak(int reading) 
{
    printf("\n[+] Sending reading to ThingSpeak: %d . . .\n", reading);
    
    http_request_t request = {0};
    
    struct altcp_pcb* pcb = altcp_tcp_new_ip_type(IPADDR_TYPE_V4);
    if (!pcb) 
    {
        printf("[-] Failed to create PCB . . .\n");
        return false;
    }
    
    request.pcb = pcb;
    altcp_arg(pcb, &request);
    altcp_recv(pcb, tcp_client_recv);
    altcp_sent(pcb, tcp_client_sent);
    
    ip_addr_t server_ip;
    ipaddr_aton(THINGSPEAK_HOST, &server_ip);
    
    printf("[+] Connecting to ThingSpeak . . .\n");

    err_t error;
    
    error = altcp_connect(pcb, &server_ip, THINGSPEAK_PORT, tcp_client_connected);
    if (error != ERR_OK) 
    {
        printf("[-] Connection failed: %d . . .\n", error);
        altcp_close(pcb);
        return false;
    }
    
    char request_buffer[256];
    snprintf(request_buffer, sizeof(request_buffer),
             "GET /update?api_key=%s&field1=%d HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n\r\n",
             THINGSPEAK_API_KEY, reading, "api.thingspeak.com");
    
    error = altcp_write(pcb, request_buffer, strlen(request_buffer), TCP_WRITE_FLAG_COPY);
    if (error != ERR_OK) 
    {
        printf("[-] Write failed: %d . . .\n", error);
        altcp_close(pcb);
        return false;
    }
    
    altcp_output(pcb);
    printf("[/] Awaiting write task completion . . .\n\n");
    
    timer_t timeout = 100;
    while (!request.complete && timeout-- > 0) 
    {
        sleep_ms(100);
    }
    
    if (request.complete) 
    {
        printf("[+] Request completed successfully . . .\n");
        return true;
    } 
    else
    {
        printf("[/] Request timed out . . .\n");
        altcp_close(pcb);
        return false;
    }
}
