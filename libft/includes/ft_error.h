/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:02:36 by helvi             #+#    #+#             */
/*   Updated: 2021/03/13 23:40:04 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "libft.h"
# include "ft_exit.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>

/*
** A struct to save all the data about a command
*/
typedef struct	s_tags
{
	char		specifier;
	int			positive_value;
	int			flag_zero;
	int			flag_minus;
	int			flag_plus;
	int			flag_space;
	int			flag_hash;
	int			flag_fd;
	int			width;
	int			width_address;
	int			precision;
	int			precision_address;
	int			length;
	int			length_hh;
	int			length_h;
	int			length_l;
	int			length_ll;
	int			length_lll;
	int			empty;
}				t_tags;

/*
**EPERM            1      Operation not permitted
**ENOENT           2      No such file or directory
**ESRCH            3      No such process
**EINTR            4      Interrupted system call
**EIO              5      I/O error
**ENXIO            6      No such device or address
**E2BIG            7      Arg list too long
**ENOEXEC          8      Exec format error
**EBADF            9      Bad file number
**ECHILD          10      No child processes
**EAGAIN          11      Try again
**ENOMEM          12      Out of memory
**EACCES          13      Permission denied
**EFAULT          14      Bad address
**ENOTBLK         15      Block device required
**EBUSY           16      Device or resource busy
**EEXIST          17      File exists
**EXDEV           18      Cross-device link
**ENODEV          19      No such device
**ENOTDIR         20      Not a directory
**EISDIR          21      Is a directory
**EINVAL          22      Invalid argument
**ENFILE          23      File table overflow
**EMFILE          24      Too many open files
**ENOTTY          25      Not a typewriter
**ETXTBSY         26      Text file busy
**EFBIG           27      File too large
**ENOSPC          28      No space left on device
**ESPIPE          29      Illegal seek
**EROFS           30      Read-only file system
**EMLINK          31      Too many links
**EPIPE           32      Broken pipe
**EDOM            33      Math argument out of domain of func
**ERANGE          34      Math result not representable
**EDEADLK         35      Resource deadlock would occur
**ENAMETOOLONG    36      File name too long
**ENOLCK          37      No record locks available
**ENOSYS          38      Function not implemented
**ENOTEMPTY       39      Directory not empty
**ELOOP           40      Too many symbolic links encountered
**EWOULDBLOCK     EAGAIN  Operation would block
**ENOMSG          42      No message of desired type
**EIDRM           43      Identifier removed
**ECHRNG          44      Channel number out of range
**EL2NSYNC        45      Level 2 not synchronized
**EL3HLT          46      Level 3 halted
**EL3RST          47      Level 3 reset
**ELNRNG          48      Link number out of range
**EUNATCH         49      Protocol driver not attached
**ENOCSI          50      No CSI structure available
**EL2HLT          51      Level 2 halted
**EBADE           52      Invalid exchange
**EBADR           53      Invalid request descriptor
**EXFULL          54      Exchange full
**ENOANO          55      No anode
**EBADRQC         56      Invalid request code
**EBADSLT         57      Invalid slot
**
**EDEADLOCK       EDEADLK
**
**EBFONT          59      Bad font file format
**ENOSTR          60      Device not a stream
**ENODATA         61      No data available
**ETIME           62      Timer expired
**ENOSR           63      Out of streams resources
**ENONET          64      Machine is not on the network
**ENOPKG          65      Package not installed
**EREMOTE         66      Object is remote
**ENOLINK         67      Link has been severed
**EADV            68      Advertise error
**ESRMNT          69      Srmount error
**ECOMM           70      Communication error on send
**EPROTO          71      Protocol error
**EMULTIHOP       72      Multihop attempted
**EDOTDOT         73      RFS specific error
**EBADMSG         74      Not a data message
**EOVERFLOW       75      Value too large for defined data type
**ENOTUNIQ        76      Name not unique on network
**EBADFD          77      File descriptor in bad state
**EREMCHG         78      Remote address changed
**ELIBACC         79      Can not access a needed shared library
**ELIBBAD         80      Accessing a corrupted shared library
**ELIBSCN         81      .lib section in a.out corrupted
**ELIBMAX         82      Attempting to link in too many shared libraries
**ELIBEXEC        83      Cannot exec a shared library directly
**EILSEQ          84      Illegal byte sequence
**ERESTART        85      Interrupted system call should be restarted
**ESTRPIPE        86      Streams pipe error
**EUSERS          87      Too many users
**ENOTSOCK        88      Socket operation on non-socket
**EDESTADDRREQ    89      Destination address required
**EMSGSIZE        90      Message too long
**EPROTOTYPE      91      Protocol wrong type for socket
**ENOPROTOOPT     92      Protocol not available
**EPROTONOSUPPORT 93      Protocol not supported
**ESOCKTNOSUPPORT 94      Socket type not supported
**EOPNOTSUPP      95      Operation not supported on transport endpoint
**EPFNOSUPPORT    96      Protocol family not supported
**EAFNOSUPPORT    97      Address family not supported by protocol
**EADDRINUSE      98      Address already in use
**EADDRNOTAVAIL   99      Cannot assign requested address
**ENETDOWN        100     Network is down
**ENETUNREACH     101     Network is unreachable
**ENETRESET       102     Network dropped connection because of reset
**ECONNABORTED    103     Software caused connection abort
**ECONNRESET      104     Connection reset by peer
**ENOBUFS         105     No buffer space available
**EISCONN         106     Transport endpoint is already connected
**ENOTCONN        107     Transport endpoint is not connected
**ESHUTDOWN       108     Cannot send after transport endpoint shutdown
**ETOOMANYREFS    109     Too many references: cannot splice
**ETIMEDOUT       110     Connection timed out
**ECONNREFUSED    111     Connection refused
**EHOSTDOWN       112     Host is down
**EHOSTUNREACH    113     No route to host
**EALREADY        114     Operation already in progress
**EINPROGRESS     115     Operation now in progress
**ESTALE          116     Stale NFS file handle
**EUCLEAN         117     Structure needs cleaning
**ENOTNAM         118     Not a XENIX named type file
**ENAVAIL         119     No XENIX semaphores available
**EISNAM          120     Is a named type file
**EREMOTEIO       121     Remote I/O error
**EDQUOT          122     Quota exceeded
**
**ENOMEDIUM       123     No medium found
**EMEDIUMTYPE     124     Wrong medium type
*/

# define EPERM            1
# define ENOENT           2
# define ESRCH            3
# define EINTR            4
# define EIO              5
# define ENXIO            6
# define E2BIG            7
# define ENOEXEC          8
# define EBADF            9
# define ECHILD          10
# define EAGAIN          11
# define ENOMEM          12
# define EACCES          13
# define EFAULT          14
# define ENOTBLK         15
# define EBUSY           16
# define EEXIST          17
# define EXDEV           18
# define ENODEV          19
# define ENOTDIR         20
# define EISDIR          21
# define EINVAL          22
# define ENFILE          23
# define EMFILE          24
# define ENOTTY          25
# define ETXTBSY         26
# define EFBIG           27
# define ENOSPC          28
# define ESPIPE          29
# define EROFS           30
# define EMLINK          31
# define EPIPE           32
# define EDOM            33
# define ERANGE          34
# define EDEADLK         35
# define ENAMETOOLONG    36
# define ENOLCK          37
# define ENOSYS          38
# define ENOTEMPTY       39
# define ELOOP           40
# define EWOULDBLOCK     EAGAIN
# define ENOMSG          42
# define EIDRM           43
# define ECHRNG          44
# define EL2NSYNC        45
# define EL3HLT          46
# define EL3RST          47
# define ELNRNG          48
# define EUNATCH         49
# define ENOCSI          50
# define EL2HLT          51
# define EBADE           52
# define EBADR           53
# define EXFULL          54
# define ENOANO          55
# define EBADRQC         56
# define EBADSLT         57

# define EDEADLOCK       EDEADLK

# define EBFONT          59
# define ENOSTR          60
# define ENODATA         61
# define ETIME           62
# define ENOSR           63
# define ENONET          64
# define ENOPKG          65
# define EREMOTE         66
# define ENOLINK         67
# define EADV            68
# define ESRMNT          69
# define ECOMM           70
# define EPROTO          71
# define EMULTIHOP       72
# define EDOTDOT         73
# define EBADMSG         74
# define EOVERFLOW       75
# define ENOTUNIQ        76
# define EBADFD          77
# define EREMCHG         78
# define ELIBACC         79
# define ELIBBAD         80
# define ELIBSCN         81
# define ELIBMAX         82
# define ELIBEXEC        83
# define EILSEQ          84
# define ERESTART        85
# define ESTRPIPE        86
# define EUSERS          87
# define ENOTSOCK        88
# define EDESTADDRREQ    89
# define EMSGSIZE        90
# define EPROTOTYPE      91
# define ENOPROTOOPT     92
# define EPROTONOSUPPORT 93
# define ESOCKTNOSUPPORT 94
# define EOPNOTSUPP      95
# define EPFNOSUPPORT    96
# define EAFNOSUPPORT    97
# define EADDRINUSE      98
# define EADDRNOTAVAIL   99
# define ENETDOWN        100
# define ENETUNREACH     101
# define ENETRESET       102
# define ECONNABORTED    103
# define ECONNRESET      104
# define ENOBUFS         105
# define EISCONN         106
# define ENOTCONN        107
# define ESHUTDOWN       108
# define ETOOMANYREFS    109
# define ETIMEDOUT       110
# define ECONNREFUSED    111
# define EHOSTDOWN       112
# define EHOSTUNREACH    113
# define EALREADY        114
# define EINPROGRESS     115
# define ESTALE          116
# define EUCLEAN         117
# define ENOTNAM         118
# define ENAVAIL         119
# define EISNAM          120
# define EREMOTEIO       121
# define EDQUOT          122

# define ENOMEDIUM       123
# define EMEDIUMTYPE     124

extern int			g_ft_errno;
extern char			*g_program_name;

char	*ft_strerror(int errnum);
void	ft_perror(const char *message);
void	ft_error(int status, int errnum, const char *format, ...);

/*
** The main function to handle printing
*/

int				ft_printer(const char *format, va_list *source);

/*
** Helper functions to set command values
*/
void			set_flag(t_tags *command, char flag);
void			set_width(t_tags *command, char c, va_list *source);
void			set_precision(t_tags *command, char c, va_list *source);
void			set_length(t_tags *command, char c);
void			set_wildcard_precision(t_tags *command, va_list *source);

/*
** The fuctions called by selector on ft_printf, main functions
** to handle different data types.
*/
int				print_s(t_tags *command, va_list *source);
int				print_c(t_tags *command, va_list *source);
int				print_p(t_tags *command, va_list *source);
int				print_d(t_tags *command, va_list *source);
int				print_o(t_tags *command, va_list *source);
int				print_u(t_tags *command, va_list *source);
int				print_x(t_tags *command, va_list *source);
int				print_f(t_tags *command, va_list *source);

/*
** Helper functions
*/
uintmax_t		read_octal(t_tags *command, va_list *source);
long long int	read_int(t_tags *command, va_list *source);
long double		read_float(t_tags *command, va_list *source);
uintmax_t		read_hexa(t_tags *command, va_list *source);
void			int_width_flag_zero(char *returnable, char *string,
					t_tags *command);
void			float_width_flag_zero(char *returnable, char *string,
					t_tags *command);
void			uint_width_flag_zero(char *returnable, char *string,
					t_tags *command);
char			*ft_trim(char *str, t_tags *command);
long double		ft_round(long double number, t_tags *command);
char			*hexa_upperalpha(char *string);
int				is_specifier(char c);

#endif
