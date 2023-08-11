/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:08:53 by maddou            #+#    #+#             */
/*   Updated: 2023/08/10 22:28:01 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
int	ft_chek_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_cut(char *sta)
{
	int		j;
	char	*new_line;

	j = 0;
	if (!sta[j])
		return (NULL);
	while (sta[j] != '\n' && sta[j] != '\0')
		j++;
	new_line = ft_calloc(j + 2, 1);
	if (!new_line)
		return (0);
	j = 0;
	while (sta[j] != '\n' && sta[j] != '\0')
	{
		new_line[j] = sta[j];
		j++;
	}
	if (sta[j] == '\n')
		new_line[j] = '\n';
	return (new_line);
}

char	*ft_chek_read(int fd, char *stash)
{
	int		y;
	char	buffer[BUFFER_SIZE + 1];

	y = 2;
	if (read(fd, 0, 0) < 0)
	{
		free(stash);
		return (0);
	}
	if (!stash)
		stash = ft_calloc(1, 1);
	while (y != 0 && ft_chek_newline(stash) != 1)
	{
		y = read(fd, buffer, BUFFER_SIZE);
		buffer[y] = 0;
		if (y == -1)
		{
			free(stash);
			return (0);
		}
		stash = ft_strjoin(stash, buffer);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_chek_read(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_cut(stash);
	stash = ft_save_next(stash);
	return (line);
}
