#include "server.h"

static int parse_int(int *res, char *str) {
	char *end = NULL;
	*res = strtol(str, &end, 10);
	if (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
		return 1;
	if (errno != 0 && val == 0)
		return 1;
	if (end == str)
		return 1;
	return *end == '\0';
}

int server_parse_args(int argc, char **argv, server_t *srv) {
	int i = 0;
	while (i < argc) {
		if (!strcmp(argv[i], "-p")) {
			i++;
			if (i >= argc) {
				PRINT_ERR("cheese: missing port parameter after `-p'\n");
				return 1;
			}
			if (parse_int(argv[i])) {
				PRINT_ERR(
					"cheese: `%s' parameter after -p is not an interger", argv[i]);
				return 1;
			}
			i++;
		}
	}
}
