/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:34:10 by aitorlope         #+#    #+#             */
/*   Updated: 2023/01/02 16:48:22 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../lib/libft/libft.h"
#include "../inc/utils.h"
#include "../inc/draw_utils.h"

/*
*	Acording the z value of the point and de max and min values of the map
*	this function set the color needed of the point received.
*	All the colors are defined in fdf.h 
*/

void	load_color(int max, int min, t_point *point, t_colors	colors)
{
	point->paint = 1;
	point->color = DEFAULT_COLOR;
	if (point->hex_color > 0)
	{
		point->color = point->hex_color;
		return ;
	}
	if (point->axis[Z] == max)
		point->color = colors.topcolor;
	else if (point->axis[Z] == 0)
		point->color = colors.groundcolor;
	else if (point->axis[Z] == min && min != 0)
		point->color = colors.bottomcolor;
	else if (point->axis[Z] > 0)
		point->color = gradient(colors.groundcolor, colors.topcolor, \
		max, point->axis[Z]);
	else
		point->color = gradient(colors.bottomcolor, colors.groundcolor, \
		-min, - (min - point->axis[Z]));
}

int	has_hexcolors(char *line)
{
	char	**color;
	int		get_color;

	if (ft_strchr(line, ',') != 0)
	{
		color = ft_split(line, ',');
		get_color = strtol(color[1] + 2, NULL, 16);
		dbl_free(color);
		return (get_color);
	}
	else
		return (0);
}

int	valid_point(char *value)
{
	int	valid;

	valid = 0;
	if (*value == '-' || *value == '+' || ft_isdigit(*value))
		valid++;
	value++;
	while (ft_isdigit(*value))
	{
		value++;
		valid++;
	}
	if (valid == 0)
		return (0);
	else
		return (1);
}

static void	map_ini_colors(t_map *map)
{
	map->colors.backcolor = BACK_COLOR;
	map->colors.menucolor = MENU_COLOR;
	map->colors.bottomcolor = BOTTOM_COLOR;
	map->colors.groundcolor = GROUND_COLOR;
	map->colors.topcolor = TOP_COLOR;
}

void	map_ini(t_map *map, int total)
{
	if (total)
	{
		map->len = 0;
		map->limits.axis[X] = 0;
		map->limits.axis[Y] = 0;
		map->limits.axis[Z] = 0;
		map->zmin = 0;
	}
	map->b_lines = 1;
	map->b_dots = 0;
	map->b_pluslines = 0;
	map->b_geo = 0;
	map->b_stars = 0;
	map->b_shadow = 1;
	map->scale = 1;
	map->zdivisor = 1;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
	map->source.axis[Z] = 0;
	map->ang[X] = 0;
	map->ang[Y] = 0;
	map->ang[Z] = 0;
	map_ini_colors(map);
}
