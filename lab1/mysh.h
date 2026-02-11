#ifndef MYSH_H
#define MYSH_H

//put in header 
#include <stdio.h>
#include <string.h>
<<<<<<< HEAD
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//execution of commands
void built_in_command(Command *cmd);
void extern_command(Command *cmd);
void io_redirection(Command *cmd);
void background_exe(Command *cmd);


//parser
int parse_command(char *line, Command *cmd);
=======
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
>>>>>>> 3a8f2ba (feat: implemented shell input)

#endif