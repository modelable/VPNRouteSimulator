#ifndef COMMAND_H
#define COMMAND_H

#include "device.h"
#include "router.h"
#include "tunnel.h"

// 명령어 처리 함수 선언
void process_command(const char* command, Device* devices, Router* router1, Router* router2, Tunnel* tunnel);

#endif