#ifndef MYSH_H
#define MYSH_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

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

int parse_command(char *line, Command *cmd);
void free_command(Command *cmd);

int execute_command(Command *cmd);

void reap_background_jobs();

#endif