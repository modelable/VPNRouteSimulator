#ifndef TUNNEL_H
#define TUNNEL_H

typedef struct Tunnel {
    char source_ip[16];
    char dest_ip[16];
} Tunnel;

void configure_tunnel(Tunnel* tunnel, const char* source_ip, const char* dest_ip);

#endif