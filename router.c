#include <stdio.h>
#include <string.h>
#include "router.h"

void router_configure_tunnel(Router* router, const char* source_ip, const char* dest_ip) {
    configure_tunnel(&router->tunnel, source_ip, dest_ip);  // 터널 설정 호출
    printf("%s 라우터에 터널 설정 완료\n", router->name);
}