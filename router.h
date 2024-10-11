#ifndef ROUTER_H
#define ROUTER_H

typedef struct {
    FastEthernet fastEthernet[2];
    StaticRoutes staticRoutes[10];
    Router *tunnel;
} Router;

typedef struct {
    char ip[16];
    char subnet[16];
} FastEthernet;

typedef struct {
    char network[16];
    char mask[16];
    char nextHop[16];
} StaticRoutes;

#endif