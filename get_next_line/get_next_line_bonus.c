/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:11:17 by maddou            #+#    #+#             */
/*   Updated: 2022/11/08 15:11:25 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	chek_newline(char *sta)
{
	int	i;

	i = 0;
	while (sta[i])
	{
		if (sta[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_cut(char *stash)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!stash[i])
		return (0);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	new_line = ft_calloc(i + 2, 1);
	if (!new_line)
		return (0);
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
	{
		new_line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		new_line[i] = '\n';
	return (new_line);
}

char	*get_chek(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		y;

	y = 2;
	if (read(fd, 0, 0) < 0)
	{
		free(stash);
		return (0);
	}
	if (!stash)
		stash = ft_calloc(1, 1);
	while (y != 0 && chek_newline(stash) != 1)
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
	static char	*sta[OPEN_MAX];
	char		*line;

	line = 0;
	if (fd < 0 && BUFFER_SIZE <= 0)
		return (0);
	sta[fd] = get_chek(fd, sta[fd]);
	if (!sta[fd])
		return (0);
	line = ft_cut(sta[fd]);
	sta[fd] = ft_save_next(sta[fd]);
	return (line);
}
