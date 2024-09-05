typedef struct Router {
    char name[20];
    char ip[16];
    char mac[18];
    char tunnel_source_ip[16];
    char tunnel_dest_ip[16];
    struct Router* next;
} Router;