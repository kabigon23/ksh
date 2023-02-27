#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KSH_RL_BUFSIZE 1024
#define KSH_TOK_BUFSIZE 64
#define KSH_TOK_DELIM " \t\r\n\a"

char* ksh_read_line(void) {
    int bufsize = KSH_RL_BUFSIZE;
    int pos = 0;
    char *buf = malloc(sizeof(char)*bufsize);
    int c;

    if (buf == NULL) {
        fprintf(stderr, "ksh: allocation error\n");
        exit(EXIT_FAILURE);        
    }

    while (1) {
        // Read a character
        c = getchar();
        
        if (c == EOF || c == '\n') {
            buf[pos] = '\0';
            return buf;
        } else {
            buf[pos] = c;
        }
        pos++;

        if (pos >= bufsize) {
            bufsize += KSH_RL_BUFSIZE;
            buf = realloc(buf, sizeof(char)*bufsize);
            if (buf == NULL) {
                fprintf(stderr, "ksh: reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char** ksh_split_line(char* line) {
    int bufsize = KSH_TOK_BUFSIZE, pos = 0;
    char** tokens = malloc(sizeof(char*)*bufsize);
    char* token;

    if (tokens == NULL) {
        fprintf(stderr, "ksh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, KSH_TOK_DELIM);
    while (token != NULL) {
        tokens[pos] = token;
        pos++;
        if (pos >= bufsize) {
            bufsize += KSH_TOK_BUFSIZE;
            tokens = realloc(tokens, sizeof(char*)*bufsize);
            if (tokens == NULL) {
                fprintf(stderr, "ksh: reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, KSH_TOK_DELIM);
    }
    tokens[pos] = NULL;
    return tokens;
}
int ksh_excute(**args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("ksh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("ksh");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && WIFSIGNALED(status));
    }
}
void ksh_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = ksh_read_line();
        args = ksh_split_line(line);
        status = ksh_excute(args);

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv) {
    // Load config files, if any.

    // Run command loop.
    ksh_loop();

    // Perform any shutdown/cleanup.

    return EXIT_SUCCESS;
}
