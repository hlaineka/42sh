/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:02:16 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/09 14:53:10 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define ERR_READ 1
# define ERR_MALLOC 2

typedef struct		s_input
{
	char			*ls; //left_side
	char			*rrs; //reverse right_side
	int				ls_i; //not needed?
	int				rrs_i; //not needed?
}					t_input;

void				init_input(t_input *input);

#endif
