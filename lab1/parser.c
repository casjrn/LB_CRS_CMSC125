#include "mysh.h"

Command parse_command(char *line)
{
    Command cmd;
    memset(&cmd, 0, sizeof(Command));

    char *token = strtok(line, " \t\r\n");
    int arg_index = 0;

    while (token != NULL)
    {
        // INPUT REDIRECTION
        if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, " \t\r\n");
            if (token)
            {
                cmd.input_file = strdup(token);
            }
        }
        // OUTPUT REDIRECTION
        else if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, " \t\r\n");
            if (token)
            {
                cmd.output_file = strdup(token);
                cmd.append = false;
            }
        }
        else if (strcmp(token, ">>") == 0)
        {
            token = strtok(NULL, " \t\r\n");
            if (token)
            {
                cmd.output_file = strdup(token);
                cmd.append = true;
            }
        }
        // BACKGROUND EXECUTION
        else if (strcmp(token, "&") == 0)
        {
            cmd.background = true;
        }
        else
        {
            if (cmd.command == NULL)
                cmd.command = strdup(token);

            if (arg_index < 255)
            {
                cmd.args[arg_index++] = strdup(token);
            }
        }

        token = strtok(NULL, " \t\r\n");
    }

    cmd.args[arg_index] = NULL;

    return cmd;
}
