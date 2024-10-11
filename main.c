#include <stdio.h>
#include <string.h>
#include "device.h"
#include "router.h"
#include "tunnel.h"

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

    char buffer[100];

	printf("=======================\n");
	printf("Test program !\n");
	printf("========================\n");

    while (1) {
		printf("prompt>> ");

		fgets(buffer, sizeof(buffer), stdin);

		command(buffer);
	}

	return 0;
}