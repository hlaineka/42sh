/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 11:58:27 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/26 12:13:18 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# define T_INT_MAX 2147483647
# define T_INT_MIN -2147483648
# define BUFF_SIZE 8
# define FD_LIMIT 4864
# define TRUE 1
# define FALSE 0

# include "libft_shorthand.h"
# include "ft_printf.h"
# include "ft_exit.h"
# include "ft_error.h"
# include "lists.h"
# include "misc.h"
# include "strings.h"
# include "stringarrays.h"

/*
** Basic functions
*/

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putnbr(int n);
void				ft_putendl(char const *s);
void				*ft_memset(void *ptr, int value, size_t num);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t num);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t num);
void				*ft_memchr(const void *ptr, int c, size_t num);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_strtoupper(char *str);

size_t				ft_strlen(char const *s);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_array_len(char const *s, char c);
size_t				ft_intlen_base(int n, int base);
size_t				ft_uintlen_base(unsigned int n, unsigned int base);
size_t				ft_uintmaxlen_base(uintmax_t n, uintmax_t base);
size_t				ft_longlonglen_base(long long n, int base);
size_t				ft_strarrlen(char **array);

char				*ft_itoa(int n);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t num);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strrcat(char *s1, const char *s2);
char				*ft_strncat(char *dest, const char *src, size_t num);
char				*ft_strchr(const char *src, int c);
char				*ft_strrchr(const char *src, int c);
char				*ft_strstr(const char *str1, const char *str2);
char				*ft_strnstr(const char *str1, const char *str2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s);
char				*ft_uintmaxtoa_base(uintmax_t n, uintmax_t base);
char				*ft_uitoa_base(unsigned int n, unsigned int base);
char				*ft_itoa_base_prefix(int n, int base, char *prefix);
char				*ft_ltoa_base(long long n, int base);
char				*ft_ltoa_base_prefix(long long n, int base, char *prefix);
char				**ft_strsplit(const char *s, char c);

int					ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strncmp(const char *str1, const char *str2, size_t num);
int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, int base);
int					ft_abs(int a);
int					get_nbr(char c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int arg);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_isoption(char *str);
int					ft_islongoption(char *str);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char *s1, const char *s2, size_t n);

double				ft_pow(double x, double y);
int					ft_log10(long double f);

/*
** List functions
*/
t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new_list);
void				ft_lstiter(t_list *lst, void (*f)(t_list*elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstsrc(const void *content, t_list *beginning);
void				ft_lstnewtoend(const void *content, size_t content_size,
						t_list **beginning);
void				ft_lstaddafter(t_list *end, t_list *newelem);
void				ft_lstappend(t_list **alst, t_list *new_lst);
void				ft_lstrev(t_list **alst);
void				ft_lstprint(t_list *lst);
void				ft_lstfree(void *data, size_t size);
int					ft_lstlen(t_list *lst);

/*
** Own adds.
*/

int					ft_define_length(int n);
char				*ft_strset(char value, size_t num);
char				*ft_strnchr(const char *src, int c);
int					ft_iscntrl(int c);

t_u32				ft_bitmask_u32(t_u32 n);
t_u64				ft_bitmask_u64(t_u64 n);

#endif
