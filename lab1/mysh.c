#include "mysh.h"

int main() {
    Command cmd;
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
