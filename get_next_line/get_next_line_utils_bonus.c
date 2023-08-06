/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:11:59 by maddou            #+#    #+#             */
/*   Updated: 2022/11/08 15:14:09 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_calloc(int count, int size)
{
	int		len;
	char	*p;
	int		i;

	len = count * size;
	i = 0;
	p = malloc(len);
	if (!p)
		return (0);
	while (i < len)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	int		i;
	int		j;
	int		len;
	char	*new_stash;

	i = 0;
	j = 0;
	len = ft_strlen(stash) + ft_strlen(buffer) + 1;
	new_stash = ft_calloc(len, 1);
	if (!new_stash)
		return (0);
	while (stash[i])
	{
		new_stash[i] = stash[i];
		i++;
	}
	while (buffer[j])
		new_stash[i++] = buffer[j++];
	free(stash);
	return (new_stash);
}

char	*ft_save_next(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	j = ft_strlen(stash);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	while (stash[i] == 0)
	{
		free(stash);
		return (0);
	}
	i++;
	new_stash = ft_calloc(j - i + 1, 1);
	if (!new_stash)
		return (0);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	free(stash);
	return (new_stash);
}
