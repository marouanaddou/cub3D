/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_information.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-gand <mel-gand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:51:35 by maddou            #+#    #+#             */
/*   Updated: 2023/08/20 11:43:22 by mel-gand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

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

void fill_information(t_cub *cub)
{
    int c;

    while(cub->par.element[cub->i] != NULL)
    {
        cub->j = 0;
        c = 0;
        cub->par.elm[cub->i].path = NULL;
        cub->par.elm[cub->i].direction = NULL;
        while(cub->par.element[cub->i][cub->j] != '\0')
        {

            if (c == 0 && cub->par.element[cub->i][cub->j] != ' ')
                cub->par.elm[cub->i].direction  = ft_copier(cub->par.element[cub->i][cub->j], 
                cub->par.elm[cub->i].direction);
            else if (c == 0 && cub->par.element[cub->i][cub->j] == ' ')
                c = 1;
            else if (c == 1)
                cub->par.elm[cub->i].path = ft_copier(cub->par.element[cub->i][cub->j], 
                cub->par.elm[cub->i].path);
            cub->j++; 
        }
        cub->i++;
    }
}

char **number_element_without_newlen(t_cub *cub, char **result)
{
    cub->i = 0;
    cub->par.cnt_elmt = 0;

    while(cub->par.element[cub->i] != NULL)
    {
        if (cub->par.element[cub->i][0] != '\n')
            cub->par.cnt_elmt++;
        cub->i++;
    }
    if (cub->par.cnt_elmt != 6) // hna khasna free .....!
    {
        printf ("ERROR: information\n");
        exit(1);
    }
    result = malloc(sizeof(char *) * (cub->par.cnt_elmt + 1));
    cub->i = 0;
    cub->j = 0;
    return (result);
}

void    split_newline_information(t_cub *cub)
{
    char **result;

    result = NULL;
    result = number_element_without_newlen(cub, result);
    while(cub->par.element[cub->i] != NULL)
    {
        if (cub->par.element[cub->i][0] != '\n')
        {
            result[cub->j] = ft_strdup(cub->par.element[cub->i]);
            cub->j++;
        }
        cub->i++;
    }
    result[cub->j] = NULL;
    cub->j = 0;
    free_double_pointer(cub->par.element);
    cub->par.element = result;
    cub->par.elm = malloc(sizeof(t_elem) * cub->par.cnt_elmt);
    cub->i = 0;
}

void    comparaison(char *direction, t_cub *cub)
{
    (void)cub;
    if (ft_strcmp(direction, "NO") != 0 
        && ft_strcmp(direction, "WE")!= 0
        && ft_strcmp(direction, "SO") != 0 
        && ft_strcmp(direction, "EA")!= 0
        && ft_strcmp(direction, "F") != 0 
        && ft_strcmp(direction, "C")!= 0)// hna khasna free .....!
    {
        printf ("ERROR: information\n");
        exit(1);
    }   
}

void check_double(t_cub *cub, int i)
{
    cub->j = 0;
    while(cub->j < cub->par.cnt_elmt)
    {
        if (cub->j != i)
        {
            if (ft_strcmp(cub->par.elm[i].direction, cub->par.elm[cub->j].direction) == 0)// hna khasna free .....!
            {
                printf ("ERROR: double information\n");
                exit(1);
            }
        }
        cub->j++;
    }
    cub->j = 0;
}

void    check_argument(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\0')
    {
        printf ("ERROR: color\n");
        exit(1);
    }
    while (str[i] != '\0')
    {
        if (ft_isdigit(str[i]) != 1)
        {
            printf ("ERROR: color\n");
            exit(1);
        }
        i++;
    }
}

void    check_rgb(char **color, t_cub *cub, char *tream, int atoi)
{
    cub->j = 0;
    atoi = 0;
    while(color[cub->j] != NULL)
    {
        if (color[cub->j + 1] == NULL)
        {
            tream = ft_strdup(ft_strtrim(color[cub->j], "\n"));
            free(color[cub->j]);
            color[cub->j] = ft_strdup(tream);
            free(tream);
        }
        check_argument(color[cub->j]);
        atoi = ft_atoi(color[cub->j]);
        if (atoi < 0 || atoi > 255)
        {
            printf ("ERROR: color\n");
            exit(1);
        }
        cub->j++;
    }
}

void    check_double_coma(t_cub *cub, char *color)
{
    cub->i = 0;
    if (color[0] == ',')
        print_error("ERROR: color\n");
    while(color[cub->i] != '\0')
    {
        if (color[cub->i] == ',' && color[cub->i + 1] == ',')
            print_error("ERROR: color\n");
        cub->i++;
    }
}

void    check_color(t_cub *cub, int i)
{
    char    **color;
    char    *tream;
    int     atoi; 
    atoi = 0;
    tream = NULL;
    check_double_coma(cub, cub->par.elm[i].path);
    color = ft_split(cub->par.elm[i].path, ',');
    check_rgb(color, cub, tream, atoi);
    if (cub->j != 3)
    {
        printf ("ERROR: color\n");
        exit(1);
    }
    
    cub->j = 0;
}

void    tream_path(t_cub *cub, int i)
{
    char *tream;

    tream = ft_strdup(ft_strtrim(cub->par.elm[i].path, " "));
    free(cub->par.elm[i].path);
    cub->par.elm[i].path = ft_strdup(tream);
    free(tream);
}

void    check_error_information(t_cub *cub)
{
    int i;
    
    i = 0;
    cub->j = 0;
    while(i < cub->par.cnt_elmt )
    {
        comparaison(cub->par.elm[i].direction, cub);
        check_double(cub, i);
        if (ft_strcmp(cub->par.elm[i].direction, "F") == 0 
            || ft_strcmp(cub->par.elm[i].direction, "C") == 0)
            check_color(cub, i);
        else 
            tream_path(cub, i);
        i++;
    }
}

void    check_information(t_cub *cub)
{
    split_newline_information(cub);
    fill_information(cub);
    check_error_information(cub);
    cub->i = 0;
    cub->j = 0;
}