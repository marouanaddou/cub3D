/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:11:16 by maddou            #+#    #+#             */
/*   Updated: 2023/04/14 22:09:33 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	free_split(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static int	ft_nmb_string(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i + 1] != '\0' && s[i + 1] != c)
		{
			j++;
			i++;
		}
		i++;
	}
	return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return (NULL);
	i = 0;
	p = malloc(len + 1);
	if (!p)
		return (0);
	while (start < ft_strlen((char *)s) && s[start + i] != '\0' && i < len)
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split(char *str, char c)
{
	int		i;
	int		j;
	int		start;
	char	**result;

	i = 0;
	j = 0;
	result = (char **)malloc((ft_nmb_string(str, c) + 1) * sizeof(char *));
	if (!result)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		start = i;
		while (str[i] != c && str[i] != '\0')
			i++;
		if ((i - start) > 0)
			result[j++] = ft_substr(str, start, (i - start));
	}
	result[j] = NULL;
	return (result);
}
