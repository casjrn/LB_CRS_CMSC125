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
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
    } else if (pid == 0) {                          // CHILD
        io_redirection(cmd);            
        execvp(cmd->command, cmd->args); 
        perror("exec failed");
        exit(127);
    } else {                                        // PARENT
        background_exe(cmd, pid);       
    }
}


void io_redirection(Command *cmd){

}



void background_exe(Command *cmd){
    
}


void reap_background_processes() {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}