/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 11:23:19 by helvi             #+#    #+#             */
/*   Updated: 2021/04/28 17:51:21 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# include "libft.h"

char				*ft_char_str_join(char c, char *s1);
char				*ft_dynamic_string(char **dest, char *src, int num);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
char				*ft_replc(char *src, int i, char *input);
char				*ft_str_addi(const char *str, int i, char c);
char				*ft_str_char_join(char c, char *s1);
void				ft_str_deli(char **str, int i);
int					ft_str_find_c(const char *src, int c);
char				*ft_str_realloc(char *src, int start, int end);
int					ft_str_rfind_c(const char *src, int c);
char				*ft_str_toupper(char *str);
char				*ft_strjoin_frees1(char *s1, char *s2);
char				*ft_strjoin_frees2(char *s1, char *s2);
char				*ft_strjoin3(char *str1, char *str2, char *str3);
char				ft_strlast(char const *str);
void				ft_strpaste_digits(char *dest, char *src);
void				ft_strpaste_end(char *dest, char *src);
void				ft_strpaste(char *dest, char *src);
char				*ft_strstr_remove(char *str1, char *str2);
int					ft_strstri(const char *str1, const char *str2);
char				*ft_strsub_freestr(char *s, unsigned int start, size_t len);
char				*ft_strsub_mid(const char *s, unsigned int start,
						size_t end);
char				*ft_remove_chars(char *str, int c);
void				ft_strtoupper(char *str);
char				*ft_strcut(char *str, int start, int end);
int					ft_is_nbrstr(char *str);

#endif
