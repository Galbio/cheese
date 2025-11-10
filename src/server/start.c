#include "server.h"

void default_init(server_t *srv) {
	srv->port = 42124;
	srv->path = NULL;
}

int server_start(int argc, char **argv) {
	server_t srv = (server_t){0};
	default_init(&srv);
	if (server_parse_args(argc, argv, &srv))
		return 1;
}
