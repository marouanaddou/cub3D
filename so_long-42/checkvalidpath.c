/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkvalidpath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:40:33 by maddou            #+#    #+#             */
/*   Updated: 2023/04/13 22:11:11 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	checkfila_wal(char **matrix, int j)
{
	int	i;

	i = 0;
	while (matrix[0][i] != '\0' && matrix[j][i] != '\0')
	{
		if (matrix[0][i] != '1' || matrix[j][i] != '1')
		{
			write(1, "not valid wall ❌\n", 20);
			free_split(matrix);
			exit(1);
		}
		i++;
	}
	return (i);
}

void	aplique(t_long *l, int x, int y)
{
	l->matrix[x][y] = '1';
	if (l->matrix[x - 1][y] != '1')
		aplique(l, x - 1, y);
	if (l->matrix[x][y + 1] != '1')
		aplique(l, x, y + 1);
	if (l->matrix[x + 1][y] != '1')
		aplique(l, x + 1, y);
	if (l->matrix[x][y - 1] != '1')
		aplique(l, x, y - 1);
}

void	c_map(t_long *l)
{
	l->i = 0;
	l->j = 0;
	l->a = 0;
	while (l->buffer[l->i] != '\0')
	{
		if (l->buffer[l->i] == '\n')
		{
			l->j++;
			l->i++;
			l->a = 0;
		}
		l->matrix[l->j][l->a] = l->buffer[l->i];
		l->a++;
		l->i++;
	}
	l->i = 0;
	l->j = 0;
}

void	validpath(t_long *l)
{
	l->i = 0;
	aplique(l, l->x, l->y);
	calcul_element(l);
	while (l->matrix[l->i] != NULL)
	{
		l->j = 0;
		while (l->matrix[l->i][l->j] != '\0')
		{
			if (l->matrix[l->i][l->j] == 'C' || l->matrix[l->i][l->j] == 'E')
			{
				write(1, "not valid path ❌\n", 19);
				free_split(l->matrix);
				exit(1);
			}
			l->j++;
		}
		l->i++;
	}
	c_map(l);
	write(1, "valid path ✅\n", 15);
}

void	check_valid_map(char **matrix, t_long *l)
{
	l->i = 1;
	l->p = 0;
	while (matrix[l->i] != NULL)
	{
		l->j = 0;
		while (matrix[l->i][l->j] != '\0')
		{
			if (matrix[l->i][l->j] == 'P')
				break ;
			l->j++;
		}
		if (matrix[l->i][l->j] == 'P')
			break ;
		l->i++;
	}
	while (l->buffer[l->p] != '\0')
		l->p++;
	l->x = l->i;
	l->y = l->j;
	validpath(l);
}
