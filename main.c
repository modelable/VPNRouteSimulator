#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 50
#define MAX_ARGS 10

typedef struct Device
{
	int id;			 // 장치의 번호
	char ip[16];	 // IP(예: 192.168.1.2)
	char subnet[16]; // 서브넷 마스크(예: 255.255.255.0)
} Device;

Device deviceList[MAX_VERTICES]; // 장치 목록

/* Queue */
typedef int element; // int(Device.id)
typedef struct
{
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void queue_init(QueueType *q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

/* Graph */
typedef struct GraphNode
{
	int vertex;
	struct GraphNode *link;
} GraphNode;

typedef struct GraphType
{
	int n;
	GraphNode *adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(GraphType *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과\n");
		return;
	}
	g->n++;
}

void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node;

	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류\n");
		return;
	}

	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

int search_ping(GraphType *g, int src, int dest)
{
	GraphNode *w;
	QueueType q;
	int visited[MAX_VERTICES] = {0};
	int v;

	queue_init(&q);
	enqueue(&q, src);
	
	visited[src] = 1;

	while (!is_empty(&q)) {
		v = dequeue(&q);

		for (w = g->adj_list[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				visited[w->vertex] = 1;
				enqueue(&q, w->vertex);
			}

			if (w->vertex == dest)
				return 1;
		}
	}

	return -1;
}

void search_tracert(GraphType *g, int src, int dest)
{
	GraphNode *w;
	QueueType q;
	int visited[MAX_VERTICES] = {0};
	int prev[MAX_VERTICES]; // 부모 노드
	int v, hop = 1;

	queue_init(&q);
	enqueue(&q, src);

	visited[src] = 1;
	prev[src] = -1;

	while (!is_empty(&q)) {
		v = dequeue(&q);

		for (w = g->adj_list[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				visited[w->vertex] = 1;
				prev[w->vertex] = v;

				enqueue(&q, w->vertex);

				if (w->vertex == dest) {
					int path[MAX_VERTICES];
					int path_length = 0;
					int temp = dest;

					while (temp != -1) {
						path[path_length++] = temp;
						temp = prev[temp];
					}

					for (int i = path_length - 1; i >= 0; i--) {
						printf("\t%d\t0 ms\t0 ms\t0 ms\t%s\n", hop++, deviceList[path[i]].ip);
					}

					return;
				}
			}
		}
	}
}

typedef int cmd_func(int argc, char *argv[], GraphType *g);

typedef struct
{
	char *cmd;		// 명령어(문자열)
	cmd_func *func; // 명령어(함수 포인터)
} CommandList;

// 명령어 "config" (예: config 192.168.1.2 255.255.255.0)
int commandConfig(int argc, char *argv[], GraphType *g)
{
	if (argc < 3) {
		printf("Usage: config <IP1> <IP2>\n");
		return -1;
	} else {
		Device device;

		device.id = g->n;
		strcpy(device.ip, argv[1]);
		strcpy(device.subnet, argv[2]);

		deviceList[g->n] = device;

		insert_vertex(g, device.id);
	}

	return 0;
}

// 명령어 "route" (예: route 192.168.2.1 2.0.0.1)
int commandRoute(int argc, char *argv[], GraphType *g)
{
	if (argc < 3) {
		printf("Usage: route <IP1> <IP2>\n");
		return -1;
	} else {
		int from = -1, to = -1;

		for (int i = 0; i < MAX_VERTICES; i++) {
			if (strcmp(deviceList[i].ip, argv[1]) == 0)
				from = deviceList[i].id;
			if (strcmp(deviceList[i].ip, argv[2]) == 0)
				to = deviceList[i].id;
		}

		if (from == -1 || to == -1) {
			printf("Error: IP not found.\n");
			return -1;
		}

		insert_edge(g, from, to);
	}

	return 0;
}

// 명령어 "ping" (예: ping 192.168.1.2 192.168.2.2)
int commandPing(int argc, char *argv[], GraphType *g)
{
	if (argc < 3) {
		printf("Usage: ping <IP1> <IP2>\n");
		return -1;
	} else {
		int src = -1, dest = -1;

		for (int i = 0; i < MAX_VERTICES; i++) {
			if (strcmp(deviceList[i].ip, argv[1]) == 0)
				src = deviceList[i].id;
			if (strcmp(deviceList[i].ip, argv[2]) == 0)
				dest = deviceList[i].id;
		}

		if (src == -1 || dest == -1) {
			printf("Error: IP not found.\n");
			return -1;
		}

		printf("Pinging %s with 32 bytes of data:\n\n", argv[1]);
		for (int i = 0; i < 4; i++) {
			sleep(1);
			if (search_ping(g, src, dest) == 1)
				printf("Reply from %s: bytes=32 time<1ms TTL=254\n", deviceList[dest].ip);
			else if (search_ping(g, src, dest) == -1)
				printf("Request timeout for icmp_seq %d\n", i);
		}

		printf("\nPing complete.\n");
	}

	return 0;
}

// 명령어 "tracert" (예: tracert 192.168.1.1 192.168.2.1)
int commandTracert(int argc, char *argv[], GraphType *g)
{
	if (argc < 3) {
		printf("Usage: tracert <IP1> <IP2>\n");
		return -1;
	} else {
		int src = -1, dest = -1;

		for (int i = 0; i < MAX_VERTICES; i++) {
			if (strcmp(deviceList[i].ip, argv[1]) == 0)
				src = deviceList[i].id;
			if (strcmp(deviceList[i].ip, argv[2]) == 0)
				dest = deviceList[i].id;
		}

		if (src == -1 || dest == -1) {
			printf("Error: IP not found.\n");
			return -1;
		}

		printf("Tracing route to %s over a maximum of %d hops:\n\n", argv[1], MAX_VERTICES);
		search_tracert(g, src, dest);
		printf("\nTrace complete.\n");
	}

	return 0;
}

// 명령어 "tunnel" (예: tunnel 192.168.1.1 192.168.2.1)
int commandTunnel(int argc, char *argv[], GraphType *g)
{
	if (argc < 3) {
		printf("Usage: tunnel <IP1> <IP2>\n");
		return -1;
	} else {
		int src = -1, dest = -1;

		// IP 주소를 찾아서 정점 인덱스를 가져옴
		for (int i = 0; i < MAX_VERTICES; i++) {
			if (strcmp(deviceList[i].ip, argv[1]) == 0)
				src = deviceList[i].id;
			if (strcmp(deviceList[i].ip, argv[2]) == 0)
				dest = deviceList[i].id;
		}

		if (src == -1 || dest == -1) {
			printf("Error: IP not found.\n");
			return -1;
		}

		// 양방향 연결
		insert_edge(g, src, dest);
		insert_edge(g, dest, src);

		printf("Tunnel created between %s and %s.\n", argv[1], argv[2]);
	}

	return 0;
}

// 명령어 목록(배열)
CommandList commandList[] = {
	{"config", commandConfig},
	{"route", commandRoute},
	{"ping", commandPing},
	{"tracert", commandTracert},
	{"tunnel", commandTunnel}
};

void command(char *cmd, GraphType *g)
{
	CommandList *p = commandList;
	int argc = 0;
	char *argv[MAX_ARGS] = {0};
	char *token = strtok(cmd, " ");

	while (token != NULL && argc < MAX_ARGS) {
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc - 1][strcspn(argv[argc - 1], "\n")] = '\0'; // 개행 문자 제거
	
	if (argc) {
		while (p->cmd) {
			if (strcmp(p->cmd, argv[0]) == 0) {
				p->func(argc, argv, g);
				break;
			} else if (strcmp("exit", argv[0]) == 0 || strcmp("quit", argv[0]) == 0) {
				exit(1);
			}
			p++;
		}
	}
}

int main()
{
	int id = 0;
	char buffer[100];
	GraphType *g = (GraphType *)malloc(sizeof(GraphType));
	graph_init(g);

	printf("Microsoft Windows [Version 10.0.22631.4317]\n");
	printf("(c) Microsoft Corporation. All rights reserved.\n\n");

	while (1) {
		printf("prompt>> ");
		fgets(buffer, sizeof(buffer), stdin);

		command(buffer, g);
	}

	free(g);

	return 0;
}