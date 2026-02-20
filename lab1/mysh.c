#include "mysh.h"

int main() {
    char line[MAX_LINE];

    while (1) {
        reap_background_processes();
        
        printf("mysh> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) break;
       
        Command cmd = parse_command(line);

        if (cmd.command != NULL) {
           if (strcmp(cmd.command, "exit") == 0 || 
            strcmp(cmd.command, "cd") == 0   || 
            strcmp(cmd.command, "pwd") == 0) {
            
            built_in_command(cmd);
            free_command(cmd); // Free built-ins immediately
            } else {
                extern_command(cmd);
            
                // if a background job, free now
                if (!cmd.background) {
                    free_command(cmd);
            }
            }
        }

    return 0;
    }
}
