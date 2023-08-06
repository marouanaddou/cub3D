/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:06:22 by maddou            #+#    #+#             */
/*   Updated: 2023/08/05 15:14:39 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print(int i)
{
	if (i == 0)
	{
		write(1, "Error name \n", 15);
		exit(1);
	}
}

void check_file_ext(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '.')
			break ;
		i++;
	}
	if (name[i + 1] != 'c')
		print(0);
	if (name[i + 2] != 'u')
		print(0);
	if (name[i + 3] != 'b')
		print(0);
	if (name[i + 4] != '\0')
		print(0);
	print(1);
}
