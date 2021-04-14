#include "parser.h"
#include <sys/stat.h>
#include <fcntl.h>



/*
** open(filename, O_RDWR | O_CREAT | O_TRUNC):
** opens the file with read and write permission, creates the file if it
** does not exists and overwrites the data on the file AND truncates all
** excess residual data left from overwrite.
*/

t_job	*token_less(t_job *job, t_term *term, t_node *current)
{

}
