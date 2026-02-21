#include "mysh.h"

int job_id = 1;
pid_t bg_pids[MAX_JOBS] = {0};
Command bg_jobs[MAX_JOBS];

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
    {
        perror("fork failed");
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
    { // PARENT
        background_exe(cmd, pid);
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
        bool tracked = false;
        for (int i = 0; i < MAX_JOBS; i++)
        {
            if (bg_pids[i] == 0)
            {
                bg_pids[i] = pid;
                bg_jobs[i] = cmd;
                // parent does NOT wait
                printf("[%d] Started: %s (PID: %d)\n", job_id++, cmd.command, pid);
                tracked = true;
                break;
            }
        }

        if (!tracked)
        {
            fprintf(stderr, "mysh: maximum background jobs reached (%d)\n", MAX_JOBS);
            free_command(cmd);
        }
    }
}

// freedom from the scraps joke

void free_command(Command cmd)
{
    if (cmd.command)
    {
        free(cmd.command);
    }
    if (cmd.input_file)
    {
        free(cmd.input_file);
    }
    if (cmd.output_file)
    {
        free(cmd.output_file);
    }

    if (cmd.args) {
        for (int i = 0; cmd.args[i] != NULL; i++)
        {
            free(cmd.args[i]);
        }
    }
}

// DEALING WITH ZOMBIES

void reap_background_processes()
{
     int status;
    pid_t pid;
    // check child
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        // find slot
        for (int i = 0; i < MAX_JOBS; i++) {
            if (bg_pids[i] == pid) {
                printf("\n[%d] Done: %s (PID: %d)\n", i + 1, bg_jobs[i].command, pid);
                
                // free memory
                free_command(bg_jobs[i]); 
                
                bg_pids[i] = 0; // clear the slot 
                break;
            }
        }
    }
}