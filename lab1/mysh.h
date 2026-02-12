#ifndef MYSH_H
#define MYSH_H

//put in header 
#include <stdio.h>
#include <string.h>
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

#endif