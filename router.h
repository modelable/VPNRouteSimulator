#ifndef ROUTER_H
#define ROUTER_H

#include "tunnel.h"

typedef struct Router {
    char name[20];
    char ip[16];
    char mac[18];
    Tunnel tunnel;  // 라우터가 사용하는 VPN 터널 정보
} Router;

void router_configure_tunnel(Router* router, const char* source_ip, const char* dest_ip);

#endif