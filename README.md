# 21sh
Next step on creating a shell that fill the requirements of POSIX

Collaborators on this project are @hlaineka and @huhtasheikki

## Features of this shell:
- Operators: ;, |, >>, >, <<, <, >&, <&, &&, || 
- Line edition using termcaps-library.
  - History of commands using up and down arrows
  - Movement in line with left and right arrows.
  - Movement word by word with shift + left and right arrows.
  - Movement one line up and down shift + up and down arrows.
  - ctrl+Y to copy line, ctrl+k to cut line, ctrl+p to paste line in app.
  - copy/paste works from outside of the app with the basic combination of keys as usual
  - Home and end to go to the beginning and end of the command.
  - Line editing over multiple lines.
- ${} handling for internal variables, ~ parsing (home directory / homedirectory of the user given after ~)
- builtins:
  - echo no options, checks that the fd is valid.
  - env with options:
  - cd with absolute and relative path, options: -
  - setenv and unsetenv to set environment variables in from 'key value'
  - exit
- ctrl+D, ctrl+C signal handling.
- Complete management of quotes (singlequotes, doublequotes and backslash)
- No leaks, no extra fd:s, error handling done by hand withour errno.
- The shell can be started with option 'debug' that prints more info of how the shell handles data.
- Allowed C-library functions in this project:
  - malloc,free
  - access
  - open,close,read,write
  - opendir,readdir,closedir
  - getcwd,chdir
  - stat,lstat,fstat
  - fork,execve
  - wait,waitpid,wait3,wait4
  - signal,kill
  - exit
  - pipe
  - dup,dup2
  - isatty,ttyname,ttyslot
  - ioctl
  - getenv
  - tcsetattr,tcgetattr
  - tgetent, tgetflag, tgetnum, tgetstr
  - tgoto, tputs

## Parsing
The shell creates tokens out of the input it receives. Operator tokens, word tokens etc are marked and advanced tokenization handles word expansions in lexer. After that the parser creates an abstract syntax tree (AST) from the token list. Operator tokens are signed a precedence value and the infix notation is changed into postfix notation with shunting yard algorithm. In our implementation postfix was selected because of the ease to transform it to binary tree. Shunting yard uses a last in first out stack to store operators, and compares the precedence values to evaluate when an operator is moved from operator stack to output. More about the algorithm https://en.wikipedia.org/wiki/Shunting-yard_algorithm

The abstact syntax tree is created from postfix notation with the help of last in first out stack (made with pointers of the tokens). The command `echo hi ; ls > file` would become `echo, hi, (null), ls, >, ;` To create the abstract syntax tree, the tokens are read from right to left. The abstract syntax tree is send to execution for job creation.

## Job creation and execution
The tree traversal checks the current operator in the tree and calls the function assigned to that operator from static const array of function pointers. If the function is not found, NULL pointer is returned. All the functions are named token_operatorname(). The jobs are created in the operator functions. Operators `;`, `|`, `&&` and `||` handle the execution of the simple commands by themselves. The job creation function that calls the tree traversal checks that all the created jobs are executed, and if not, executes them.

## External links
https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html the bible of this project, shell command language definition in POSIX by Open Group.
