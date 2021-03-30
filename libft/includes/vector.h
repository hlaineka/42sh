/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:08:00 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/27 21:22:13 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct	s_vector_list
{
	char		**data;
	size_t		limit;
	size_t		current;
}				t_vector_list;

typedef struct s_vector t_vector;

struct				s_vector
{
	t_vector_list	vector_list;
	int				(*init)(void);
	size_t			(*len)(t_vector *vector);
	size_t			(*strlen)(t_vector *vector, int i);
	int				(*push_back)(t_vector *vector);
	int				(*push_front)(t_vector *vector);
	int				(*push_mid)(t_vector *vector, int i);
	char			**(*get)(t_vector *vector);
	char			*(*get_str)(t_vector *vector, int i);
	int				(*del)(t_vector *vector, int i);
	int				(*free)(t_vector *vector);

};

int				vector_init(void);
size_t			vector_len(t_vector *vector);
size_t			vector_strlen(t_vector *vector, int i);
int				vector_push_back(t_vector *vector);
int				vector_push_front(t_vector *vector);
int				vector_push_mid(t_vector *vector, int i);
char			**vector_get(t_vector *vector);
char			*vector_get_str(t_vector *vector, int i);
int				vector_del(t_vector *vector, int i);
int				vector_free(t_vector *vector);