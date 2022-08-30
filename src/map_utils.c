/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:26:27 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 13:26:30 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/draw_utils.h"

/* 
*	This function iterate all the points of the wire array and draw a line between:
*	--> wire[i] and wire [i+1]
*	--> wire[i] and wire [i + mapsize]
*/

void	wired(t_meta *meta, t_point *wire)
{
	int	i;

	i = 0;
	while (i < meta->map.len)
	{
		if (wire[i].paint)
		{
			if ((i + 1) % (int)meta->map.limits.axis[X] != 0)
			{
				draw_line(meta, wire[i], wire[i + 1]);
				if (meta->map.b_pluslines)
				{
					if ((i / (int)meta->map.limits.axis[X]) != \
						(meta->map.limits.axis[Y] - 1))
						draw_line(meta, wire[i], wire[i + \
							(int)meta->map.limits.axis[X] + 1]);
				}
			}
			if ((i / (int)meta->map.limits.axis[X]) != \
			(meta->map.limits.axis[Y] - 1))
				draw_line(meta, wire[i], wire[i + (int)meta->map.limits.axis[X]]);
		}
		i++;
	}
}

/* 
*	Colorize all the points of the map
*/

void	colorize(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->len)
	{
		load_color((int)map->limits.axis[Z], map->zmin, \
		&map->points[i], map->colors);
		i++;
	}
}

/* 
*	This function iterate all the points of the array and draw a dot for each point
*/

void	doted(t_meta *meta, t_point *proyect)
{
	int	i;

	i = 0;
	while (i < meta->map.len)
	{
		if (proyect[i].paint)
			draw_dot(meta, proyect[i], 1);
		i++;
	}
}

/* 
*	This function iterate len points of the array and 
*	divide de z axis by divisor
*/

void	z_division(t_point *proyect, float divisor, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		proyect[i].axis[Z] = proyect[i].axis[Z] / divisor;
		i++;
	}
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
	map->scale = 1;
	map->zdivisor = 1;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
	map->source.axis[Z] = 0;
	map->ang[X] = 0;
	map->ang[Y] = 0;
	map->ang[Z] = 0;
	map->colors.backcolor = BACK_COLOR;
	map->colors.menucolor = MENU_COLOR;
	map->colors.bottomcolor = BOTTOM_COLOR;
	map->colors.groundcolor = GROUND_COLOR;
	map->colors.topcolor = TOP_COLOR;
}
