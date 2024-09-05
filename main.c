#include <stdio.h>
#include <string.h>
#include "device.h"
#include "router.h"
#include "tunnel.h"
#include "command.h"

int main() {
    // 장비 및 라우터 설정
    Device* devices = NULL;
    Router router1, router2;
    Tunnel tunnel;

    devices = add_device(devices, "PC0", "192.168.1.2", "00A1.B2C3.D4E5");
    devices = add_device(devices, "PC1", "192.168.2.2", "00F1.G2H3.I4J5");

    // 라우터 설정
    strcpy(router1.name, "Router1");
    strcpy(router1.ip, "192.168.1.1");
    strcpy(router1.mac, "00D0.16A7.B801");

    strcpy(router2.name, "Router2");
    strcpy(router2.ip, "192.168.2.1");
    strcpy(router2.mac, "00D0.BCAE.7601");

    // 콘솔에서 명령어 입력 처리
    char command[100];
    while (1) {
        printf("명령어를 입력하세요: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // 입력된 명령어에서 개행 문자 제거
        process_command(command, devices, &router1, &router2, &tunnel);
    }

    return 0;
}