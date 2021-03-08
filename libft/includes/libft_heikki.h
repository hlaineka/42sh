/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:10:51 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/03 20:22:22 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_HEIKKI_H
# define LIBFT_HEIKKI_H

# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include "libft_shorthand.h"
# include "ft_printf_heikki.h"

# define MAX_FD 4000

int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isspace(int c);
int					ft_isoption(char *str);
int					ft_islongoption(char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, int base);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					get_next_line(const int fd, char **line);
int					ft_abs(int a);
int					get_nbr(char c);
int					ft_iscntrl(int c);

char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_itoa(int n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,\
								size_t len);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				*ft_itoa_base_prefix(int n, int base, char *prefix);
char				*ft_uitoa_base(unsigned int n, unsigned int base);
char				*ft_uintmaxtoa_base(uintmax_t n, uintmax_t base);
char				*ft_ltoa_base(long long n, int base);
char				*ft_ltoa_base_prefix(long long n, int base, char *prefix);
char				*ft_ftoa(long double f, size_t prec);
char				**ft_strarrdel(char ***arr);

char				**ft_strsplit(char const *s, char c);

void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memmove(void *dst, const void *src, size_t len);

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_bzero(void *s, size_t n);
void				ft_memdel(void **ap);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_strtoupper(char *str);

size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_array_len(char const *s, char c);
size_t				ft_intlen_base(int n, int base);
size_t				ft_uintlen_base(unsigned int n, unsigned int base);
size_t				ft_uintmaxlen_base(uintmax_t n, uintmax_t base);
size_t				ft_longlonglen_base(long long n, int base);
size_t				ft_strarrlen(char **array);

double				ft_pow(double x, double y);
int					ft_log10(long double f);
unsigned long long	ft_logbase2(unsigned long long val);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstappend(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstrev(t_list **alst);
void				ft_lstprint(t_list *lst);
void				ft_lstfree(void *data, size_t size);
int					ft_lstlen(t_list *lst);

/*
** FLOATING POINT VARIABLE FUNCTIONS
*/
double				ft_frexp(double x, int *exp);

/*
** BITMASK FUNTIONS
*/
t_u32				ft_bitmask_u32(t_u32 n);
t_u64				ft_bitmask_u64(t_u64 n);

/*
** VARIABLE LENGTH QUATITY FUNCTIONS
*/
t_u64				*ft_vlqnew(t_u32 size);

#endif
