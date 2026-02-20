#include "mysh.h"

void built_in_command(Command cmd)
{

    if (cmd.command == NULL)
        return; // empty

    // EXIT
    else if (strcmp(cmd.command, "exit") == 0)
    {
        exit(0);
    }

    // CD
    else if (strcmp(cmd.command, "cd") == 0)
    {

        if (cmd.args[1] == NULL)
        {
            fprintf(stderr, "mysh: cd: missing argument\n");
        }
        else
        {
            // path does not exist
            if (chdir(cmd.args[1]) != 0)
            {
                perror("mysh: cd");
            }
        }
    }

    // PWD
    else if (strcmp(cmd.command, "pwd") == 0)
    {
        char *cwd = getcwd(NULL, 0); // dangerous stuff
        if (cwd != NULL)
        {
            printf("%s\n", cwd);
            free(cwd); // free memory
        }
        else
        {
            perror("mysh: pwd");
        }
    }
}

void extern_command(Command cmd)
{
    pid_t pid = fork();

    if (pid < 0)
    { // PARENT
        background_exe(cmd, pid);
    }
    else if (pid == 0)
    { // CHILD
        io_redirection(cmd);

        // execute
        execvp(cmd.command, cmd.args);
        perror("exec failed");
        exit(127);
    }
    else
    {
        perror("fork failed");
    }
}

void io_redirection(Command cmd)
{
    if (cmd.input_file)
    {
        int fd = open(cmd.input_file, O_RDONLY);

        if (fd < 0)
        {
            perror("open input");
            exit(1);
        }

        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (cmd.output_file)
    {
        int flags = O_WRONLY | O_CREAT | (cmd.append ? O_APPEND : O_TRUNC);
        int fd = open(cmd.output_file, flags, 0644);

        if (fd < 0)
        {
            perror("open output");
            exit(1);
        }

        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void background_exe(Command cmd, pid_t pid)
{
    if (!cmd.background)
    {
        int status;
        waitpid(pid, &status, 0); // parent pauses here
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf("Command exited with code %d\n", WEXITSTATUS(status));
        }
    }
    else
    {
        // parent does NOT wait
        printf("[%d] Started: %s (PID: %d)\n", job_id++, cmd.command, pid);
    }
}

void free_command(Command cmd){
    if (cmd.command) {free(cmd.command);}
    if (cmd.input_file) {free(cmd.input_file);}
    if (cmd.output_file) {free(cmd.output_file);}
    for (int i = 0; cmd.args[i] != NULL; i++) {
        free(cmd.args[i]);
    }
}

void reap_background_processes()
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}