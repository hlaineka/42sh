/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarrays.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:12:22 by helvi             #+#    #+#             */
/*   Updated: 2021/04/06 11:14:30 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGARRAYS_H
# define STRINGARRAYS_H

# include "libft.h"

char				**ft_addstr(char **dest, char *src);
int					ft_array_length(char **array);
char				**ft_strarr_add(char **arr, char *str);
char				**ft_strarr_addfront(char **arr, char *str);
char				**ft_strarr_copy(char **src);
void				ft_strarray_free(char **strarr);

#endif
