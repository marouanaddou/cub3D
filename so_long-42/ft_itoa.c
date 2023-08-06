/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:42:00 by maddou            #+#    #+#             */
/*   Updated: 2023/04/14 22:09:29 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	calcul_nb(int nbr)
{
	int	n;

	n = 1;
	if (nbr < 10)
		return (n);
	while (nbr / 10 > 0)
	{
		n++;
		nbr = nbr / 10;
	}
	return (n);
}

char	*ft_itoa(int nbr)
{
	int		number;
	char	*str;

	number = calcul_nb(nbr);
	str = malloc(number + 1 * sizeof(char));
	str[number] = '\0';
	number--;
	while (nbr / 10 > 0)
	{
		str[number--] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	if (nbr >= 0 && nbr <= 9)
		str[number] = nbr + 48;
	return (str);
}
