# Source files of the project excluding libft library functions.

1. Builtins, all the builtins of the shell
    - alias
    - bg
    - cd
    - echo
    - env (not in use in this implementation, but is used by some other functions)
    - exit
    - export
    - fc
    - fg
    - hash
    - jobs
    - set
    - setenv (not in use in this implementation, but is used by some other functions)
    - test
    - type
    - unalias
    - unset
    - unsetenv (not in use in this implementation, but is used by some other functions)
    - also error handling for builtins as well as few helper functions

2. Execution, the execution of the commands
    - job_creation with recursive function to create jobs from the AST-tree made by parser as well as functions for every token or operation
    - Helper functions for execution

3. init
    - initializing functions for start of the shell (as well as some for exiting)

4. input
    - Functions that handle user input, as well as history handling

5. job_control
    - Functions used in job controlling

6. parser
    - the main function of parser, as well as separate folders for tokenization and AST-tree creation

7. signal
    - Functions responsible for signal handling

8. main.c
    - the main function and a few helper functions to keep the wheels turning.
