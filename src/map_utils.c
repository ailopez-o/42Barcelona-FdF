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
		if ((i + 1) % (int)meta->map.limits.axis[x] != 0)
			draw_line(meta, wire[i], wire[i + 1]);
		if ((i / (int)meta->map.limits.axis[x]) != (meta->map.limits.axis[y] - 1))
			draw_line(meta, wire[i], wire[i + (int)meta->map.limits.axis[x]]);
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
		load_color((int)map->limits.axis[z], map->zmin, &map->points[i], map->colors);
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
		draw_dot(meta, proyect[i], 1);
		i++;
	}
}

/* 
*	This function copy len points of the array from src to dst
*/

void	copy_map(t_point *src, t_point *dst, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
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
		proyect[i].axis[z] = proyect[i].axis[z] / divisor;
		i++;
	}
}

void	map_ini(t_map *map)
{
	map->b_lines = 1;
	map->b_dots = 0;
	map->renders = 0;
	map->scale = 1;
	map->zdivisor = 1;
	map->brange = 0;
	map->source.axis[x] = XCENTER;
	map->source.axis[y] = YCENTER;
	map->source.axis[z] = 0;
	map->ang[x] = 0;
	map->ang[y] = 0;
	map->ang[z] = 0;
	map->colors.backcolor = BACK_COLOR;
	map->colors.menucolor = MENU_COLOR;
	map->colors.bottomcolor = BOTTOM_COLOR;
	map->colors.groundcolor = GROUND_COLOR;
	map->colors.topcolor = TOP_COLOR;
}
