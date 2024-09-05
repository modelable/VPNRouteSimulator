#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "device.h"

// 장비 추가 함수 구현
Device* add_device(Device* head, const char* name, const char* ip, const char* mac) {
    Device* new_device = (Device*)malloc(sizeof(Device));
    strcpy(new_device->name, name);
    strcpy(new_device->ip, ip);
    strcpy(new_device->mac, mac);
    new_device->next = head;
    return new_device;
}