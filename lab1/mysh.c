#include "mysh.h"

Command cmd;

void reap_background_processes() {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    char line[MAX_LINE];

    while (1) {
        reap_background_processes();
        
        printf("mysh> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin))
            break;

        if (strlen(line) <= 1) continue;

        if (parse_command(line)) {
           built_in_command(&cmd);
        }

    return 0;
    }
}
