#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"

void process_command(const char* command, Device* devices, Router* router1, Router* router2, Tunnel* tunnel) {
    // ping
    if (strncmp(command, "ping", 4) == 0) {
        char target_ip[16];
        sscanf(command, "ping %15s", target_ip);
        printf("Ping 명령어 처리: %s로 ping...\n", target_ip);
    }
    // 터널 IP 주소 설정
    else if (strncmp(command, "ip address", 10) == 0) {
        char tunnel_ip[16];
        char subnet_mask[16];
        sscanf(command, "ip address %15s %15s", tunnel_ip, subnet_mask);
        printf("터널 IP 주소 설정: %s, 서브넷 마스크: %s\n", tunnel_ip, subnet_mask);
    }
    // 터널 소스 설정
    else if (strncmp(command, "tunnel source", 13) == 0) {
        char source_interface[16];
        sscanf(command, "tunnel source %15s", source_interface);
        printf("터널 소스 설정: %s\n", source_interface);
    }
    // 터널 목적지 설정
    else if (strncmp(command, "tunnel destination", 18) == 0) {
        char dest_interface[16];
        sscanf(command, "tunnel destination %15s", dest_interface);
        printf("터널 목적지 설정: %s\n", dest_interface);
    }
    // clear
    else if (strcmp(command, "clear") == 0) {
        printf("\033[H\033[J");  // 터미널 화면 클리어
        printf("화면이 클리어되었습니다.\n");
    }
    // quit
    else if (strcmp(command, "quit") == 0) {
        printf("프로그램을 종료합니다.\n");
        exit(0);
    }
    else {
        printf("알 수 없는 명령어입니다: %s\n", command);
    }
}