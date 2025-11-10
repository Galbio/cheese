#ifndef SERVER_H
#define SERVER_H

#include <oeuf.h>
#include "cheese.h"

/*
server args:
	-p PORT: set the port (default 42124)
	--path PATH: set the PWD (default ./)
*/


#define CLIENT_NAME_LEN 20

#define PRINT_ERR(...) fprintf(stderr, __VA_ARGS__)

typedef struct {
	int fd;
	int is_registered;
	char name[CLIENT_NAME_LEN + 1];
	buffer_t buffer;
} client_info_t;

typedef struct {
	int fd;
	int port;
	char *path;
	oe_hashmap_t clients;
} server_t;

int server_parse_args(int argc, char **argv, server_t *srv);
int server_start(int argc, char **argv);

#endif
