/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarrays.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:12:22 by helvi             #+#    #+#             */
/*   Updated: 2021/02/25 12:15:03 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGARRAYS_H
# define FT_STRINGARRAYS_H

# include "libft.h"

char				**ft_addstr(char **dest, char *src);
int					ft_array_length(char **array);
char				**ft_strarr_add(char **arr, char *str);
char				**ft_strarr_addfront(char **arr, char *str);
char				**ft_strarr_copy(char **src);
void				ft_strarray_free(char **strarr);

#endif