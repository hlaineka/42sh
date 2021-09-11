/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 09:42:02 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/11 17:32:06 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

/*
** MAC OS ERROR NUMBERS
*/
# define E_PERM 1
# define E_NOENT 2
# define E_SRCH 3
# define E_INTR 4
# define E_IO 5
# define E_NXIO 6
# define E_2BIG 7
# define E_NOEXEC 8
# define E_BADF 9
# define E_CHILD 10
# define E_DEADLK 11
# define E_NOMEM 12
# define E_ACCES 13
# define E_FAULT 14
# define E_NOTBLK 15
# define E_BUSY 16
# define E_EXIST 17
# define E_XDEV 18
# define E_NODEV 19
# define E_NOTDIR 20
# define E_ISDIR 21
# define E_INVAL 22
# define E_NFILE 23
# define E_MFILE 24
# define E_NOTTY 25
# define E_TXTBSY 26
# define E_FBIG 27
# define E_NOSPC 28
# define E_SPIPE 29
# define E_ROFS 30
# define E_MLINK 31
# define E_PIPE 32
# define E_DOM 33
# define E_RANGE 34
# define E_AGAIN 35
# define E_INPROGRESS 36
# define E_ALREADY 37
# define E_NOTSOCK 38
# define E_DESTADDRREQ 39
# define E_MSGSIZE 40
# define E_PROTOTYPE 41
# define E_NOPROTOOPT 42
# define E_PROTONOSUPPORT 43
# define E_SOCKTNOSUPPORT 44
# define E_NOTSUP 45
# define E_PFNOSUPPORT 46
# define E_AFNOSUPPORT 47
# define E_ADDRINUSE 48
# define E_ADDRNOTAVAIL 49
# define E_NETDOWN 50
# define E_NETUNREACH 51
# define E_NETRESET 52
# define E_CONNABORTED 53
# define E_CONNRESET 54
# define E_OBUFS 55
# define E_ISCONN 56
# define E_NOTCONN 57
# define E_SHUTDOWN 58
# define E_TIMEDOUT 60
# define E_CONNREFUSED 61
# define E_LOOP 62
# define E_NAMETOOLONG 63
# define E_HOSTDOWN 64
# define E_HOSTUNREACH 65
# define E_NOTEMPTY 66
# define E_PROCLIM 67
# define E_USERS 68
# define E_DQUOT 69
# define E_STALE 70
# define E_BADRPC 72
# define E_RPCMISMATCH 73
# define E_PROGUNAVAIL 74
# define E_PROGMISMATCH 75
# define E_PROCUNAVAIL 76
# define E_NOLCK 77
# define E_NOSYS 78
# define E_FTYPE 79
# define E_AUTH 80
# define E_NEEDAUTH 81
# define E_PWROFF 82
# define E_DEVERR 83
# define E_OVERFLOW 84
# define E_BADEXEC 85
# define E_BADARCH 86
# define E_SHLIBVERS 87
# define E_BADMACHO 88
# define E_CANCELED 89
# define E_IDRM 90
# define E_NOMSG 91
# define E_ILSEQ 92
# define E_NOATTR 93
# define E_BADMSG 94
# define E_MULTIHOP 95
# define E_NODATA 96
# define E_NOLINK 97
# define E_NOSR 98
# define E_NOSTR 99
# define E_PROTO 100
# define E_TIME 101
# define E_OPNOTSUPP 102
# define E_HEADERSTRING 103

# define E_TOO_FEW_ARGS 104
# define E_TOO_MANY_ARGS 105
# define E_ONLYALNUM 106
# define E_FIRST_ALPHA 107
# define E_FORK 108
# define E_ILLEGAL_OPTION 109
# define E_CD_CHANGE_FAIL 110
# define E_HOME_NOT_SET 111
# define E_INVALID_INPUT 112
# define E_NO_COMMAND 113
# define E_ENV_PATH_NOT_SET 114
# define E_NO_SUCH_JOB 115
# define E_BIN_OP_EXP 116
# define E_UNA_OP_EXP 117
# define E_NOT_INT 118
# define E_NOT_FOUND 119
# define E_EXPORT_FAIL 120

typedef struct stat	t_stat;

#endif
