# [CMSC 125 Lab 1] Unix Shell



#### Creators:
Chrystie Rae Sajorne 
Leona Mae Blancaflor

#### Description
This laboratory activity is to design and implement a simple UNIX-like shell in C. The shell is capable of accepting user commands, creating child processes, and executing system programs using appropriate system calls. The program supports basic built-in commands and follow proper software engineering practices such as modularity, version control, and documentation.

#### Features
- Execute built-in commands (cd, pwd, exit)
- Execute standard commands (ls, cat, echo)
- Supports input (<) and output redirection (> and >>)
- Runs background commands (&)
- Handles multiple arguments
- Manages processes using fork(), exec(), and wait()
- Parses input

#### Code structure
- mysh.h - command struct and function declarations
- mysh.c - main shell loop
- parser.c - parses command lines into Command struct
- interpreter.c - executes the command

#### Example
mysh> ls
DESIGN.md  FETCH_HEAD  Makefile  interpreter.c  mysh  mysh.c  mysh.h  parser.c


