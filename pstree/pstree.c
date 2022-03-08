#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define VERSION "Version: 0.0.1\n"

struct process_state {
	int pid;
	char name[30];
	char state;
	int ppid;
};

struct node {
	struct process_state ps;
	struct node *next;
	struct node *child;
};
void node_init(struct node *n);
int node_add(struct node *sn, struct node *fn);
void node_destroy(struct node *fn);

static struct option longopts[] = {
	{ "show-pids",		0, NULL, 'p' },
	{ "numeric-sort",	0, NULL, 'n' },
	{ "version",		0, NULL, 'V' },
	{ 0,				0, 0,	 0   }
};

int isNumber(char *str);
void getProcessState(struct node *head);
void printProcess(struct node *head);
void printVersion();

int main(int argc, char *argv[]) {
	char opt;
	int option_index;
	struct node *head;

	head = (struct node *)malloc(sizeof(struct node));
	node_init(head);
	getProcessState(head);

	if (argc == 1) {
		printProcess(head);
	}
	else {
		while ((opt = getopt_long(argc, argv, "pnV", longopts, &option_index)) != -1) {
			switch (opt) {
			case 'p':
				break;
			case 'n':
				break;
			case 'V':
				break;
			default:
				exit(1);
			}
			printf("%c\n", opt);
		}
	}

	node_destroy(head);

	return 0;
}

int isNumber(char *str) {
	for (char *c = str; *c != '\0'; c ++ )
		if (isdigit(*c) == 0)
			return 0;
	return 1;
}

void node_init(struct node *n) {
	n->ps = (struct process_state){ 0, { }, 0 };
	n->child = NULL;
	n->next = NULL;
}

int node_add(struct node *sn, struct node *fn) {
	struct node *p;
	
	if (sn->ps.ppid == fn->ps.pid) {
		if (fn->child == NULL)
			fn->child = sn;
		else {
			for (p = fn->child; p->next != NULL; p = p->next)
				;
			p->next = sn;
		}
		return 1;
	}
	else {
		for (p = fn->child; p != NULL; p = p->next)
			if (node_add(sn, p))
				return 1;
		return 0;
	}
}

void node_destroy(struct node *fn) {
	struct node *p = fn->child;

	if (p != NULL)
		for ( ; p != NULL; ) {
			struct node *tmp = p;
			p = p->next;
			node_destroy(tmp);
		}
	
	free(fn);
}

void getProcessState(struct node *head) {
	DIR *d;
	struct dirent *dir;
	FILE *f;
	char path[30] = "/proc/";

	d = opendir("/proc");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (isNumber(dir->d_name)) {
				strcpy(path + 6, dir->d_name);
				strcat(path, "/stat");
				f = fopen(path, "r");
				if (f) {
					struct node *node;

					node = (struct node *)malloc(sizeof(struct node));
					node_init(node);
					fscanf(f, "%d (%[^)]) %c %d",
							&node->ps.pid, node->ps.name, &node->ps.state, &node->ps.ppid);
					node_add(node, head);

					/* printf("%d %s %d\n", */
							/* node->ps.pid, node->ps.name, node->ps.ppid); */

					fclose(f);
				}
				else {
					fprintf(stderr, "Open Failed\n");
				}
			}
		}
		closedir(d);
	}
}

void printProcess(struct node *n) {
	if (n->ps.pid != 0)
		fprintf(stdout, "%d %s\n", n->ps.pid, n->ps.name);

	for (struct node *p = n->child; p != NULL; p = p->next)
		printProcess(p);
}

void printVersion() {
	fprintf(stdout, VERSION);
}
