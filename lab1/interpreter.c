#include "mysh.h"

void built_in_command(Command* cmd){
    //EXIT
    if (strcmp(cmd->command, "exit") == 0){
        exit(0);

    } 

    //CD
    else if (strcmp(cmd->command, "cd") == 0){

        if (cmd->args[1] == NULL) {
            fprintf(stderr, "mysh: cd: missing argument\n"); 

        } else {
                // path does not exist
            if (chdir(cmd->args[1]) != 0) {
                perror("mysh: cd"); 
            }
        }

    } 
    
    //PWD
    else if (strcmp(cmd->command, "pwd") == 0){
        char *cwd = getcwd(NULL, 0);                //dangerous stuff
        if (cwd != NULL) {
            printf("%s\n", cwd);
            free(cwd);                              //free memory
        } else {
            perror("mysh: pwd");
        }
    }

}

void extern_command(Command *cmd){

}


void io_redirection(Command *cmd){

}



void background_exe(Command *cmd, pid_t pid){
    
}
