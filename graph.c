#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 50
#define MAX_ARGS 10

typedef struct Device {
    int id;                 //장치의 번호
    char ip[16];            //192.168.1.2
    char subnet[16];        //서브넷 마스크(예: 255.255.255.0)
    struct Device* next;    //연결된 장치
} Device;

Device deviceList[MAX_VERTICES];

/* Queue */
typedef int element;
typedef struct { 
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void queue_init(QueueType *q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType *q) {
	return (q->front == q->rear);
}

int is_full(QueueType *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q) {
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

/* Graph */
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;	
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과\n");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		printf("debug(insert) ==> %d, %d, %d\n", u, v, g->n);
		fprintf(stderr, "그래프: 정점 번호 오류\n");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void search_tracert(GraphType* g, int v, int dest) {
	
	GraphNode* w;
	QueueType q;
	int visited[MAX_VERTICES] = { 0 };
	int count = 2;	
	
	queue_init(&q);    			
	visited[v] = 1;
	
	printf("\t1\t0 ms\t0 ms\t 0 ms\t%s\n", deviceList[v].ip);  
	
	enqueue(&q, v);	
			 
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = g->adj_list[v]; w; w = w->link) {
			
			if (!visited[w->vertex]) {
				visited[w->vertex] = 1;
				printf("\t%d\t0 ms\t0 ms\t 0 ms\t%s\n", count++, deviceList[w->vertex].ip);  
				enqueue(&q, w->vertex);	
			}
			if (w->vertex == dest)
				break;
		}
	}
}

int cmd_continue = 0;

typedef int cmd_func(int argc, char* argv[], GraphType *g);

//명령어 목록(구조체)
typedef struct {
	char* cmd;      //명령어(문자열)
	cmd_func* func; //명령어(함수 포인터)
} CommandList;

//명령어 "config" (예: config 192.168.1.2 255.255.255.0)
int commandConfig(int argc, char* argv[], GraphType *g) {
	if (argv[1] == NULL) {
		printf("올바른 형식의 명령을 입력하세요.\n");
		return -1;
	} else {
		Device device;
		
		device.id = g->n;
		strcpy(device.ip, argv[1]);
		strcpy(device.subnet, argv[2]);
		device.next = NULL;

		deviceList[g->n] = device;

		insert_vertex(g, device.id);
	}

	return 0;
}

//명령어 "route" (예: route 192.168.2.1 2.0.0.1)
int commandRoute(int argc, char* argv[], GraphType *g) {
	if (argv[1] == NULL) {
		printf("올바른 형식의 명령을 입력하세요.\n");
		return -1;
	} else {
		argv[2][strcspn(argv[2], "\n")] = '\0'; // 개행 문자 제거
		int from, to;

		for (int i = 0; i < MAX_VERTICES; i++) {
			if (strcmp(deviceList[i].ip, argv[1]) == 0)
				from = deviceList[i].id;
			if (strcmp(deviceList[i].ip, argv[2]) == 0)
				to = deviceList[i].id;
		}
		insert_edge(g, from, to);
	}

	return 0;
}

//명령어 "ping" (예: ping 192.168.1.1 192.168.2.1)
int commandPing(int argc, char* argv[], GraphType *g) {
	if (argv[1] == NULL) {
		printf("올바른 형식의 명령을 입력하세요.\n");
		return -1;
	} else {
		bfs_list(g, 0, 1);
		printf("\n");
		printf("PING %s (%s): 56 data bytes\n");

// Request timeout for icmp_seq 0
// Request timeout for icmp_seq 1
// Request timeout for icmp_seq 2
// Request timeout for icmp_seq 3
// Request timeout for icmp_seq 4
// Request timeout for icmp_seq 5
// Request timeout for icmp_seq 6
// ^C
// --- 192.168.1.1 ping statistics ---
// 8 packets transmitted, 0 packets received, 100.0% packet loss
	}	
	return 0;
}

//명령어 "tracert" (예: tracert 192.168.1.1 192.168.2.1)
int commandTracert(int argc, char* argv[], GraphType *g) {
	if (argv[1] == NULL) {
		printf("올바른 형식의 명령을 입력하세요.\n");
		return -1;
	} else {
		argv[2][strcspn(argv[2], "\n")] = '\0'; // 개행 문자 제거
		int src, dest;

		for (int i = 0; i < MAX_VERTICES; i++) {
			if (strcmp(deviceList[i].ip, argv[1]) == 0)
				src = deviceList[i].id;
			if (strcmp(deviceList[i].ip, argv[2]) == 0)
				dest = deviceList[i].id;
		}
		//printf("tracert debug: src = %d, dest = %d\n", src, dest);

		printf("Tracing route to %s over a maximum of %d hops:\n\n", argv[1], MAX_VERTICES);		
		search_tracert(g, src, dest);
		printf("\nTrace complete.\n");
	}
	return 0;
}

//명령어 "clear"
int commandClear(int argc, char* argv[], GraphType *g) {
	if (argv[1] == NULL) {

	}
	else {
        
	}
	return 0;
}

//명령어 "tunnel"
int commandTunnel(int argc, char* argv[], GraphType *g) {
	if (argv[1] == NULL) {

	}
	else {
        
	}
	return 0;
}

//명령어 목록(배열)
CommandList commandList[] = {
	{"config",	commandConfig},
	{"route",	commandRoute},
// 	{"ping",	commandPing},
 	{"tracert",	commandTracert},
// //    {"clear",   commandClear},
// //	{"clear",   commandTunnel}
};

void command(char* cmd, GraphType *g) {
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
				p->func(argc, argv, g);
				break;
			} else if (strcmp("exit\n", argv[0]) == 0) {
				exit(1);
			}
			p++;
		}
	}
}

int main() {
	int id = 0;
	char buffer[100];
	GraphType *g = (GraphType *)malloc(sizeof(GraphType));
	graph_init(g);

	printf("Microsoft Windows [Version 10.0.22631.4317]\n");
    printf("(c) Microsoft Corporation. All rights reserved.\n");
	
	while (1) {
		printf("prompt>> ");

		fgets(buffer, sizeof(buffer), stdin);

		command(buffer, g);
	}
	
	free(g);
	return 0;
}