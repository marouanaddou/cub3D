/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_element.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:05:24 by maddou            #+#    #+#             */
/*   Updated: 2023/08/06 17:08:47 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


// void check_element(t_cub *cub)
// {
//     int x;

//     cub->i = 0;
//     cub->j = 0;
//     x = 0;
//     while (cub->par.element[cub->i] != NULL)
//     {
//         if(cub->par.element[cub->i][0] == 'N')
//         {
//             if(cub->par.element[cub->i][1] != 'O')
//             {
//                 printf ("ERROR: element\n");
//                 exit(1);
//             }
//         }
//         else if(cub->par.element[cub->i][0] == 'S')
//         {
//             if(cub->par.element[cub->i][1] != 'O')
//             {
//                 printf ("ERROR: element\n");
//                 exit(1);
//             }
//         }
//         else if(cub->par.element[cub->i][0] == 'W')
//         {
//             if(cub->par.element[cub->i][1] != 'E')
//             {
//                 printf ("ERROR: element\n");
//                 exit(1);
//             }
//         }
//         else if(cub->par.element[cub->i][0] == 'E')
//         {
//             if(cub->par.element[cub->i][1] != 'A')
//             {
//                 printf ("ERROR: element\n");
//                 exit(1);
//             }
//         }
//         else if(cub->par.element[cub->i][0] == 'F')
//         {
//             if(cub->par.element[cub->i][1] != ' ')
//             {
//                 printf ("ERROR: element\n");
//                 exit(1);
//             }
//         }
//         else if(cub->par.element[cub->i][0] == 'C')
//         {
//             if(cub->par.element[cub->i][1] != ' ')
//             {
//                 printf ("ERROR: element\n");
//                 exit(1);
//             }
//         }
//         if (cub->par.element[cub->i][0] != '\n')
//             x++;
//     }
// }
int find_end(char *element, int *i)
{
    while(element[*i] != '\0' && element[*i] != ' ')
        (*i)++;
    return (*i);
}

char	*ft_copier(char add, char *new_data)
{
	int		nb;
	int		i;
	char	*new;

	nb = 0;
	i = 0;
	if (new_data != NULL)
		nb = ft_strlen(new_data);
	new = malloc(sizeof(char) * (nb + 2));
	if (!new)
		return (0);
	if (new_data != NULL)
	{
		while (new_data[i] != '\0')
		{
			new[i] = new_data[i];
			i++;
		}
	}
	new[i++] = add;
	new[i] = '\0';
	free(new_data);
	return (new);
}

void check_element(t_cub *cub)
{
    int c;
    char *result[3];

    cub->i = 0;
    cub->j = 0;
    while(cub->par.element[cub->i] != NULL)
    {
        cub->j = 0;
        result[0] = NULL;
        result[1] = NULL;
        c = 0;
        if (cub->par.element[cub->i][cub->j] != '\n')
        {
            while(cub->par.element[cub->i][cub->j] != '\0')
            {
                if (c == 0 && cub->par.element[cub->i][cub->j] != ' ')
                {
                    result[0] = ft_copier(cub->par.element[cub->i][cub->j], result[0]);
                }
                else if (c == 0 && cub->par.element[cub->i][cub->j] == ' ')
                    c = 1;
                else if (c == 1)
                    result[1] = ft_copier(cub->par.element[cub->i][cub->j], result[1]);
                cub->j++; 
            }
            result[2] = NULL;
            printf ("%s\n %s", result[0], result[1]);
        }
        cub->i++;
    }


}

void check_map_element(t_cub *cub)
{
    (void)cub;
    check_element(cub);
}