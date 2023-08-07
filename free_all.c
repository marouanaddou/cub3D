/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:53:14 by maddou            #+#    #+#             */
/*   Updated: 2023/08/07 14:54:46 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_double_pointer(char **result)
{
    int i;

    i = 0;
    while(result[i]  != NULL)
    {
        free(result[i]);
        i++;
    }
    free(result);
}