/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sreach_enemy_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:24:11 by maddou            #+#    #+#             */
/*   Updated: 2023/04/14 22:20:11 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	sreach_enemy(t_long *l)
{
	l->w = 0;
	while (l->matrix[l->w] != NULL)
	{
		l->s = 0;
		while (l->matrix[l->w][l->s] != '\0')
		{
			if (l->matrix[l->w][l->s] == 'N')
				break ;
			l->s++;
		}
		if (l->matrix[l->w][l->s] == 'N')
			break ;
		l->w++;
	}
}
