/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:20:52 by helvi             #+#    #+#             */
/*   Updated: 2021/02/25 12:39:15 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MISC_H
# define FT_MISC_H

# include "libft.h"

int					ft_define_base_length(long long int n, int base);
void				ft_free(void *variable);
char				*ft_getenv(char **envp_pointer, char *name);
int					ft_is_whitespace(const char c);
char				*ft_itoa_base(long long int n, long long int base);
char				*ft_itoa_float(long double n);
char				*ft_itoa_hexa(uintmax_t n);
char				*ft_itoa_uint(uintmax_t n, unsigned int	base);
int					get_next_line(const int fd, char **line);
void				print_error_and_exit(char *name);
void				print_error(char *directory_name);

#endif