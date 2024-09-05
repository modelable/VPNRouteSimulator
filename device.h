typedef struct PC {
    char name[20];
    char ip[16];
    char mac[18];
    struct PC* next;
} PC;