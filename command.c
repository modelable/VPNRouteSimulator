#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_ARGS 10

int cmd_continue = 0;

typedef int cmd_func(int argc, char* argv[]);

//명령어 목록(구조체)
typedef struct {
	char* cmd;      //명령어(문자열)
	cmd_func* func; //명령어(함수 포인터)
} CommandList;

//명령어 목록(배열)
CommandList commandList[] = {
	{"ping",	commandPing},
	{"tracert",	commandTracert},
	{"exit",	commandExit},
    {"clear",   commandClear}
};

//명령어 "ping"
int commandPing(int argc, char* argv[]) {
	if (argv[1] == NULL) {
	
	}
	else {
	
	}	
	return 0;
}

//명령어 "tracert"
int commandTracert(int argc, char* argv[]) {
	if (argv[1] == NULL) {

	}
	else {

	}
	return 0;
}

//명령어 "exit"
int commandExit(int argc, char* argv[]) {
	if (argv[1] == NULL) {

	}
	else {
        
	}
	return 0;
}

//명령어 "clear"
int commandClear(int argc, char* argv[]) {
	if (argv[1] == NULL) {

	}
	else {
        
	}
	return 0;
}

void command(char* cmd)
{
	CommandList* p = commandList;
	int argc = 0;
	char* argv[MAX_ARGS] = {0,};
	char* token = strtok(cmd, " "); //문자열 분할

    while (token != NULL && argc < MAX_ARGS) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

	if (argc) {
		while (p->cmd) {
			if (strcmp(p->cmd, argv[0]) == 0) {
				p->func(argc, argv);
				break;
			}
			p++;
		}
	}
}