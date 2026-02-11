#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "mysh.h"

void reap_background_jobs() {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main() {
    char line[MAX_LINE];
    Command cmd;

    while (1) {
        reap_background_jobs();

        printf("mysh> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin))
            break;

        if (strlen(line) <= 1) continue;

        if (parse_command(line, &cmd))
            execute_command(&cmd);
    }

    return 0;
}
