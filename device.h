#ifndef DEVICE_H
#define DEVICE_H

typedef struct Device {
    char name[20];
    char ip[16];
    char subnet[16];
    struct Device* next;
} Device;

#endif