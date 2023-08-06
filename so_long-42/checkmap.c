/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:41:28 by maddou            #+#    #+#             */
/*   Updated: 2023/04/13 23:13:24 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_resolution(char *str)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	while (str[j] != '\0')
	{
		if (str[j] == '\n')
			x++;
		j++;
	}
	if (str[j] == '\0')
		x++;
	if (i > 40 || x > 15)
	{
		write(1, "resolution not convenient ❌\n", 30);
		exit(1);
	}
}

void	number_element(char *str, t_long *l)
{
	int	i;

	l->c = 0;
	l->e = 0;
	l->p = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'C')
			l->c += 1;
		else if (str[i] == 'E')
			l->e += 1;
		else if (str[i] == 'P')
			l->p += 1;
		i++;
	}
	if (l->p > 1 || l->p == 0 || l->e > 1 || l->e == 0 || l->c == 0)
	{
		write(1, "not valid elment ❌\n", 22);
		exit(1);
	}
}

void	check_length(char **matrix)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 1;
	while (matrix[0][i] != '\0')
		i++;
	while (matrix[j] != NULL)
	{
		x = 0;
		while (matrix[j][x] != '\0')
			x++;
		if (x != i)
		{
			write(1, "length not valid ❌\n", 21);
			free_split(matrix);
			exit(1);
		}
		j++;
	}
	write(1, "valid length ✅\n", 17);
}

void	check_element(char *str, t_long *l)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'C' && str[i] != 'E'
			&& str[i] != 'P')
		{
			if (str[i] == '\n' && str[i - 1] != '1' && str[i - 1] != '0'
				&& str[i - 1] != 'C' && str[i - 1] != 'E' && str[i - 1] != 'P')
			{
				write(1, "not valid elment ❌\n", 22);
				exit(1);
			}
			else if (str[i] != '\n' || (str[i] == '\n' && str[i + 1] == '\0'))
			{
				write(1, "not valid elment ❌\n", 22);
				exit(1);
			}
		}
		i++;
	}
	number_element(str, l);
	write(1, "good element ✅\n", 17);
}

void	check_wall(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[j] != NULL)
		j++;
	j--;
	i = checkfila_wal(matrix, j);
	while (--j > 0)
	{
		if (matrix[j][0] != '1' || matrix[j][i - 1] != '1')
		{
			write(1, "not valid wall ❌\n", 20);
			free_split(matrix);
			exit(1);
		}
	}
	write(1, "valid wall ✅\n", 15);
}
