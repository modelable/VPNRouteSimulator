#ifndef DEVICE_H
#define DEVICE_H

typedef struct Device {
    char name[20];
    char ip[16];
    char mac[18];
    struct Device* next;
} Device;

Device* add_device(Device* head, const char* name, const char* ip, const char* mac);

#endif