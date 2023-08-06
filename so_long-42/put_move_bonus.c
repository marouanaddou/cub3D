/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_move_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:29:47 by maddou            #+#    #+#             */
/*   Updated: 2023/04/14 22:21:02 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_cont(t_long *l)
{
	l->put_move = ft_itoa(l->cont_move);
	mlx_string_put(l->mx_init, l->mx_window, 0, 0, 000000, l->put_move);
	if (l->put_move != NULL)
		free(l->put_move);
}
