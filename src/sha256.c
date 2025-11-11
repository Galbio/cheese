#include "cheese.h"
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

static void close_pipes(int p1[2], int p2[2]) {
	close(p1[0]);
	close(p1[1]);
	close(p2[0]);
	close(p2[1]);
}

char *sha256(char *str) {
	int pipe_read[2] = {-1, -1};
	int pipe_write[2] = {-1, -1};

	if (pipe(pipe_read) < 0)
		return NULL;
	if (pipe(pipe_write) < 0) {
		close_pipes(pipe_read, pipe_write);
		return NULL;
	}

	int pid = fork();
	if (pid < 0) {
		close_pipes(pipe_read, pipe_write);
		return NULL;
	}

	if (pid == 0) {
		if (dup2(pipe_read[1], 1) < 0 || 0 > dup2(pipe_write[0], 0)) {
			close_pipes(pipe_read, pipe_write);
			exit(1);
		}
		close_pipes(pipe_read, pipe_write);
		execvp("shasum", (char *[]){"shasum", "-a", "256", NULL});
		exit(1);
	}
	write(pipe_write[1], str, strlen(str));
	close(pipe_write[0]);
	close(pipe_write[1]);
	pipe_write[0] = -1;
	pipe_write[1] = -1;
	int status = 0;
	if (waitpid(pid, &status, 0) < 0 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
		close_pipes(pipe_read, pipe_write);
		kill(pid, 9);
		return NULL;
	}
	char *res = malloc(64 + 1);
	int end = 0;
	while (1) {
		if (end >= 64)
			break;
		int ret = read(pipe_read[0], &res[end], 64 - end);
		printf("%.*s\n", end, res);
		if (ret < 0) {
			free(res);
			res = NULL;
			break;
		}
		if (ret == 0)
			break;
		end += ret;
	}
	if (end < 64) {
		free(res);
		res = NULL;
	}
	else 
		res[64] = '\0';
	close_pipes(pipe_read, pipe_write);
	return res;
}
