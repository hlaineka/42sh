# 42sh shell 
### made by @hlaineka and @huhtasheikki as a part of our Hive Helsinki studies

To compile, download the whole repo and `make` on the root folder. The executable will be named 42sh.
Makefile has rules all, libft (to only compile the library), clean, fclean and re.

The shell should not quit in an unexpected way in any situtation. If you find a bug causing a unexpected quit (segfault, bus error, double free etc) please inform us! The shell should also have no leaks, and it should not get stuck in a loop.

Allowed functions in this project:
  * The whole man 2 section
  * All the functions allowed in other minishells
  * Every functions of the termcaps library
  
Basic libc functions are written by us and are located in libft folder, named with a leading ft_. For some bonus features other ready made functions are allowed.

The use of global variables are allowed only when the use of them is defendable.

Features of the project:
1. Minishell prerequisites
  * Prompt display
  * Run commands with their parameters and PATH monitoring
  * Error monitoring, without using erno, and return values of commands

2. 21sh prerequisites and optional features
  * Operators: ;, |, >>, >, <<, <, >&, <&, &&, || 
  * Line edition using termcaps-library.
  * History of commands using up and down arrows
  * Movement in line with left and right arrows.
  * Movement word by word with shift + left and right arrows.
  * Movement one line up and down shift + up and down arrows.
  * ctrl+Y to copy line, ctrl+k to cut line, ctrl+p to paste line in app.
  * copy/paste works from outside of the app with the basic combination of keys as usual
  * Home and end to go to the beginning and end of the command.
  * Line editing over multiple lines.
  * ${} handling for internal variables, ~ parsing (home directory / homedirectory of the user given after ~)
  * builtins:
    * echo no options, checks that the fd is valid.
    * cd with absolute and relative path, options: -
    * setenv and unsetenv to set environment variables in from 'key value'
    * exit
  * ctrl+D, ctrl+C signal handling.

3. 42sh mandatory features
  * Operators as in 21sh, plus && and || and &
  * Monitoring of the shell intern and environment variables with creation of variables with name=variable leading a command.
  * builtins filling the posix requirements:
    * echo
    * cd, with flags -L and -P and handling of CDPATH
    * exit with return correct return values
    * type
    * export
    * set (not POSIX-compliant, no flags)
    * unset
    * jobs
    * fg
    * bg
    * env, setenv and unsetenv not implemented in this version

4. Modular parts
  * Complete management of quotes (singlequotes, doublequotes and backslash)
  * Tilde expansion and additional parameter formats:
     * ~
     * ${parameter:-word}
     * ${parameter:=word}
     * ${parameter:?word}
     * ${parameter:+word}
     * ${#parameter}
     * ${parameter%}
     * ${parameter%%}
     * ${parameter#}
     * ${parameter##}
  * Complete management of the history:
     * Expansions:
        ∗ !!
        ∗ !word
        ∗ !number
        ∗ !-number
     * Saving to a file so that it can be used over several sessions
     * Built-in fc (all POSIX options)
     * Incremental search in the history with CTRL-R
  * Alias management via built-ins alias and unalias
  * A hash table and built-in hash to interact with it

5. Other features
  * No leaks, no extra fd:s, error handling done by hand withour errno.
  * The shell can be started with option 'debug' that prints more info of how the shell handles data.
  * The shell can be started with option script that can run unit test files for example `./42sh script scripts/basic_tests.txt`

