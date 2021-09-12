/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:27:47 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/11 17:56:22 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

/*
** not yet done: ERR_PATH_NOT_SET, ERR_INVALID_INPUT
** if (error_no == E_TOO_FEW_ARGS)
** 		ft_printf_fd(STDERR_FILENO, "%s: Too few arguments.\n", name);
** 	if (error_no == E_TOO_MANY_ARGS)
** 		ft_printf_fd(STDERR_FILENO, "%s: Too many arguments.\n", name);
** 	if (error_no == E_ONLYALNUM)
**		ft_printf_fd(STDERR_FILENO, "%s: Variable name must contain
**			alphanumeric characters.\n", name);
**	if (error_no == E_FIRST_ALPHA)
**		ft_printf_fd(STDERR_FILENO, "%s: Variable name must begin with a
**		letter.\n", name);
*/

static const char	*g_errstr[] = {
	"\0",
	"Operation not permitted",
	"No such file or directory",
	"No such process",
	"Interrupted function call",
	"Input/output error",
	"No such device or address",
	"Arg list too long",
	"Exec format error",
	"Bad file descriptor",
	"No child processes",
	"Resource deadlock avoided",
	"Cannot allocate memory",
	"Permission denied",
	"Bad address",
	"Not a block device",
	"Resource busy",
	"File exists",
	"Improper link",
	"Operation not supported by device",
	"Not a directory",
	"Is a directory",
	"Invalid argument",
	"Too many open files in system",
	"Too many open files",
	"Inappropriate ioctl for device",
	"Text file busy",
	"File too large",
	"Device out of space",
	"Illegal seek",
	"Read-only file system",
	"Too many links",
	"Broken pipe",
	"Numerical argument out of domain",
	"Numerical result out of range",
	"Resource temporarily unavailable",
	"Operation now in progress",
	"Operation already in progress",
	"Socket operation on non-socket",
	"Destination address required",
	"Message too long",
	"Protocol wrong type for socket",
	"Protocol not available",
	"Protocol not supported",
	"Socket type not supported",
	"Not supported",
	"Protocol family not supported",
	"Address family not supported by protocol family",
	"Address already in use",
	"Cannot assign requested address",
	"Network is down",
	"Network is unreachable",
	"Network dropped connection on reset",
	"Software caused connection abort",
	"Connection reset by peer",
	"No buffer space available",
	"Socket is already connected",
	"Socket is not connected",
	"Cannot send after socket shutdown",
	"MYSTERIOUS ERROR NUMBER #59",
	"Operation timed out",
	"Connection refused",
	"Too many levels of symbolic links",
	"File name too long",
	"Host is down",
	"No route to host",
	"Directory not empty",
	"Too many processes",
	"Too many users",
	"Disc quota exceeded",
	"Stale NFS file handle",
	"MYSTERIOUS ERROR NUMBER #71",
	"RPC struct is bad",
	"RPC version wrong",
	"RPC prog. not avail",
	"Program version wrong",
	"Bad procedure for program",
	"No locks available",
	"Function not implemented",
	"Inappropriate file type or format",
	"Authentication error",
	"Need authenticator",
	"Device power is off",
	"Device error",
	"Value too large to be stored in data type",
	"Bad executable (or shared library)",
	"Bad CPU type in executable",
	"Shared library version mismatch",
	"Malformed Mach-o file",
	"Operation canceled",
	"Identifier removed",
	"No message of desired type",
	"Illegal byte sequence",
	"Attribute not found",
	"Bad message",
	"Reserved",
	"No message available",
	"Reserved",
	"No STREAM resources",
	"Not a STREAM",
	"Protocol error",
	"STREAM ioctl() timeout",
	"Operation not supported on socket",
	"------BUILTIN OWN ERROR MESSAGES-------",
	"Too few arguments",
	"Too many arguments",
	"Variable name must contain alphanumeric characters",
	"Variable name must begin with a letter",
	"Fork: Resource temporarily unavailable",
	"illegal option",
	"chdir failed",
	"Environment HOME is not set",
	"Invalid input",
	"Command not found",
	"Environment PATH is not set",
	"no such job",
	"binary operator expected",
	"unary operator expected",
	"integer expression expected",
	"not found",
	"unable to export file"
};

int	err_builtin(int error_no, char *name, char *arg)
{
	ft_printf_fd(STDERR_FILENO, "42sh: %s: %s", name, g_errstr[error_no]);
	if (arg)
		ft_printf_fd(STDERR_FILENO, ": %s", arg);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}
