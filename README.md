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

Mandatory features of the project:
  * Prompt display
  * Run commands with their parameters and PATH monitoring
  * Error monitoring, without using erno, and return values of commands
  
