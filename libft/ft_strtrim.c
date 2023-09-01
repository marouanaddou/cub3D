/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:52:23 by maddou            #+#    #+#             */
/*   Updated: 2023/08/31 18:51:58 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*p;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && check(set, s1[i]))
		i++;
	len = ft_strlen(s1);
	len--;
	while (check(set, s1[len]) && len > i && s1[i])
		len--;
	p = malloc((len - i) + 2);
	if (!p)
		return (NULL);
	while (i <= len)
		p[j++] = s1[i++];
	p[j] = '\0';
	return (p);
}
