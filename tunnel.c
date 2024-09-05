#include <stdio.h>
#include <string.h>
#include "tunnel.h"

// 터널 설정 함수 구현
void configure_tunnel(Tunnel* tunnel, const char* source_ip, const char* dest_ip) {
    strcpy(tunnel->source_ip, source_ip);
    strcpy(tunnel->dest_ip, dest_ip);
    printf("터널 설정 완료 (Source: %s, Destination: %s)\n", source_ip, dest_ip);
}