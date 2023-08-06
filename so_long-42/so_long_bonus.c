/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:07:59 by maddou            #+#    #+#             */
/*   Updated: 2023/04/14 22:37:34 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	chek_file(int maps)
{
	if (maps < 0)
	{
		write(1, "file unavaible ❌\n", 19);
		exit(1);
	}
	else
		write(1, "valid file ✅\n", 16);
}

void	print(int i)
{
	if (i == 0)
	{
		write(1, "error name ❌\n", 15);
		exit(1);
	}
	else
		write(1, "valid name ✅\n", 16);
}

int	check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			break ;
		i++;
	}
	if (str[i + 1] != 'b')
		print(0);
	if (str[i + 2] != 'e')
		print(0);
	if (str[i + 3] != 'r')
		print(0);
	if (str[i + 4] != '\0')
		print(0);
	print(1);
	return (1);
}

void	check_map(t_long *l)
{
	l->i = 0;
	l->j = 2;
	while (l->j != 0)
	{
		l->j = read(l->maps, l->buffer, 1000000);
		if (l->j == -1)
			return ;
	}
	check_resolution(l->buffer);
	check_element(l->buffer, l);
	l->matrix = ft_split(l->buffer, '\n');
	check_length(l->matrix);
	check_wall(l->matrix);
	check_valid_map(l->matrix, l);
}

int	main(int argc, char *argv[])
{
	t_long	s;
	t_mlx	mlx;

	s.cont_move = 0;
	if (argc > 1)
	{
		check_name(argv[1]);
		s.maps = open(argv[1], O_RDONLY);
		chek_file(s.maps);
		check_map(&s);
		s.mx_init = mlx_init();
		if (s.mx_init == NULL)
			return (0);
		s.mx_window = mlx_new_window(s.mx_init, s.v * 63, s.u * 63, "so_long");
		if (s.mx_window == NULL)
		{
			mlx_destroy_window(s.mx_init, s.mx_window);
			return (0);
		}
		put_image(&s, &mlx);
		put_cont(&s);
		mlx_key_hook(s.mx_window, key_hok, &s);
		mlx_hook(s.mx_window, 17, 0, game_over, &s);
		mlx_loop(s.mx_init);
	}
}
