#include "server.h"

int server_start(int argc, char **argv) {
	server_t srv = (server_t){0};
	if (server_parse_args(argc, argv, &srv))
		return 1;
}
