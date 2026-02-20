#ifndef MYSH_H
#define MYSH_H

//put in header 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_JOBS 100

typedef struct {
    char *command;
    char *args[256];
    char *input_file;
    char *output_file;
    bool append;
    bool background;
} Command;

extern int job_id = 1;

void reap_background_processes();
Command parse_command(char *line);
void built_in_command(Command cmd);
void extern_command(Command cmd);
void io_redirection(Command cmd);
void background_exe(Command cmd, pid_t pid);
void free_command(Command cmd);

#endif