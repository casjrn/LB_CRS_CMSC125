# LB_CRS_CMSC125



#### Members:
Chrystie Rae Sajorne \
Leona Mae Blancaflor

#### Week 1 Progress Report

#### 1. Problem Analysis
The objective of this laboratory activity is to design and implement a simple UNIX-like shell in C. The shell must be capable of accepting user commands, creating child processes, and executing system programs using appropriate system calls. The program should also support basic built-in commands and follow proper software engineering practices such as modularity, version control, and documentation.

Must have:
Parsing user input correctly
Distinguishing between built-in commands and external programs
Managing processes using fork(), exec(), and wait()
Ensuring clean program termination and error handling
Coordinating group work using GitHub with clear commit history

####  2. Architecture
The shell follows a read–parse–execute loop architecture.

Program flow:
Display a shell prompt
Read user input
Parse input into command and arguments
Check for built-in commands

For not built-in processes:
Create a child process using fork()
Execute the command using execvp()
Parent waits for child to finish
Repeat until exit command or EOF

Modularization 
The implementation is structured into logical components:
Input handling – reads command line input
Parser – tokenizes input into arguments
Built-in handler – handles commands like cd and exit
Executor – runs external commands via system calls


Makefile must have the following:
all
clean
different objects (if needed)

#### 3. Design Decisions
Language: C
Chosen for direct access to low-level system calls and alignment with OS concepts discussed in class.

System Calls:
fork() for process creation
execvp() for command execution
wait() for synchronization

Command Parsing:
Input is tokenized using whitespace delimiters for simplicity in the initial implementation.

Built-in Commands:
Implemented internally since commands like cd must modify the parent process state.

Version Control:
GitHub is used with frequent, meaningful commits to track individual contributions.

#### 4. Timeline
Week 1: Planning how to approach the problem 
Week 2: Implement all needed functionalities and testing
Week 3: Finalization and ensuring everything that is needed is met, and possible early defense to have ample time for refactoring



