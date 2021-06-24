#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define COMMAND_MAX 100 //maximum command line length

//0 : normal, 1: >, 2: <, 3: |
int detect_type(char **args, int arg_len, int *position) {
	int type = 0;
	int i;
	for(i=0; i<arg_len; ++i) {
		if(strcmp(args[i], ">") == 0) {
			type = 1;
			break;
		} else if(strcmp(args[i], "<") == 0) {
			type = 2;
			break;
		} else if(strcmp(args[i], "|") == 0) {
			type = 3;
			break;
		}
	}
	*position = i;
	return type;
}

void run(char **args, int arg_len) {
	fflush(stdin);
	//background detect
	int background = 0;
	if (strcmp(args[arg_len-1], "&") == 0) {
		background = 1;
		args[arg_len-1] = NULL;
		arg_len -= 1;
	}

	//redirect and pipe detect
	int position;
	int type;
	type = detect_type(args, arg_len, &position);

	//process run
	pid_t pid = fork();

	if(pid < 0) {
		fprintf(stderr, "Fork failed");
		return;
	} else if(pid == 0) {
		switch(type) {
			//normal execute
			case 0:
				execvp(args[0], args);
				break;
			//redirect >
			case 1: {
				args[position] = NULL;
				int fd = open(args[position+1], O_RDWR | O_CREAT | O_TRUNC, 777);
				dup2(fd, STDOUT_FILENO);
				close(fd);
				execvp(args[0], args);


				exit(0);
				break;
			}
			//redirect <
			case 2: {
				args[position] = NULL;
				int fd = open(args[position+1], O_RDONLY, 777);
				dup2(fd, STDIN_FILENO);
				close(fd);
				execvp(args[0], args);

				exit(0);
				break;
			}
			//pipe |
			case 3: {
				args[position] = NULL;
				pid_t pid_pipe;
				int fd[2];

				pipe(fd);

				pid_pipe = fork();
				if (pid_pipe > 0) {
					close(fd[1]);
					dup2(fd[0], STDIN_FILENO);
					wait(NULL);
					execvp(args[position+1], args+position+1);
					close(fd[0]);
					exit(0);
				} else if (pid_pipe == 0) {
					close(fd[0]);
					dup2(fd[1], STDOUT_FILENO);
					execvp(args[0], args);
					close(fd[1]);
					exit(0);
				}
				break;
			}
		}
	} else {
		if(background == 0) {
			wait(NULL);
		}
	}
	return;
}


int main(void) {
	char *args[COMMAND_MAX/2 + 1] = {NULL, };
	char command[COMMAND_MAX + 1];
	int should_run = 1;

	while(should_run) {
		printf("osh> ");

		//initialize section
		fflush(stdout);
		fflush(stdin);
		strcpy(command, ""); // init command
		for(int i=0; i<COMMAND_MAX/2+1; ++i) {
			args[i] = NULL;
		}

		//command input
		fgets(command, COMMAND_MAX+1, stdin);
		int command_len = strlen(command);
		if (command_len == 0) {
			continue;
		}
		char *ptr = strtok(command, " \n");
		int arg_len = 0;
		while (ptr != NULL) {
			args[arg_len] = malloc(strlen(ptr) + 1);
			strcpy(args[arg_len], ptr);
			arg_len += 1;
			ptr = strtok(NULL, " \n");
		}

		//excute
		run(args, arg_len);

		if (strcmp(args[0],"exit") == 0) {
			should_run = 0;
		}
	}

	return 0;
}

