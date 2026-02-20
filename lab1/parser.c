#include "mysh.h"

Command parse_command(char *line)
{
    memset(&cmd, 0, sizeof(Command));

    char *token = strtok(line, " \t\n");
    int arg_index = 0;

    while (token != NULL)
    {
        if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, " \t\n");
            if (token){
                cmd.input_file = strdup(token);
            }
        }
        else if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, " \t\n");
            if (token){
                cmd.output_file = strdup(token);
                cmd.append = false;
            }
        }
        else if (strcmp(token, ">>") == 0)
        {
            token = strtok(NULL, " \t\n");
            if (token)
            {
                cmd.output_file = strdup(token);
                cmd.append = true;
            }
        }
        else if (strcmp(token, "&") == 0)
        {
            cmd.background = true;
        }
        else
        {
            if (cmd.command == NULL)
                cmd.command = strdup(token);

            cmd.args[arg_index++] = strdup(token);
        }

        token = strtok(NULL, " \t\n");
    }

    
    cmd.args[arg_index] = NULL;
    
    return cmd;
}
