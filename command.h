#ifndef COMMAND_H
#define COMMAND_H

#define MAX_ARGS 10

typedef int cmd_func(int argc, char* argv[]);

// 명령어 목록(구조체)
typedef struct {
    char* cmd;      // 명령어(문자열)
    cmd_func* func; // 명령어(함수 포인터)
} CommandList;

// 명령어 목록(배열)
extern CommandList commandList[];

// 명령어 함수들 선언
int commandPing(int argc, char* argv[]);
int commandTracert(int argc, char* argv[]);
int commandExit(int argc, char* argv[]);
int commandClear(int argc, char* argv[]);
int commandSet(int argc, char* argv[]);
int commandTunnel(int argc, char* argv[]);

// 명령어 처리 함수
void command(char* cmd);

#endif // COMMAND_H