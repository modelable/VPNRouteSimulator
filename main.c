#include <stdio.h>
#include <string.h>
#include "device.h"
#include "router.h"
#include "command.h"

int main() {
    
    char buffer[100];

    printf("Microsoft Windows [Version 10.0.22631.4317]\n");
    printf("(c) Microsoft Corporation. All rights reserved.\n");
	
    while (1) {
		printf("prompt>> ");

		fgets(buffer, sizeof(buffer), stdin);

		command(buffer);
	}

	return 0;
}