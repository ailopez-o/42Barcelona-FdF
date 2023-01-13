/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:26:27 by aitorlope         #+#    #+#             */
/*   Updated: 2023/01/13 22:37:16 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/draw_utils.h"
#include "../lib/ft_printf/inc/ft_printf.h"

void	wire_line(t_point *point, t_meta *meta, int density, int line);

/* 
*	This function iterate all the points of the wire array and draw a line between:
*	--> wire[i] and wire [i + density]
*	--> wire[i] and wire [i + x_max * density]
*/

void	wired(t_meta *meta, t_point *wire)
{
	int	i;
	int	density;

	density = 8 / meta->map.scale;
	if (density == 0)
		density = 1;
	i = 0;
	while (i < meta->map.len)
	{
		wire_line (&wire[i], meta, density, i / meta->map.limits.axis[X]);
		i = i + meta->map.limits.axis[X] * density;
	}
}

void	wire_line(t_point *point, t_meta *meta, int density, int line)
{
	int	i;
	int	x_end;
	int	y_end;

	i = 0;
	while (i < (int)meta->map.limits.axis[X])
	{
		x_end = i + density;
		if (x_end >= (int)meta->map.limits.axis[X])
			x_end = (int)meta->map.limits.axis[X] - 1;
		y_end = i + (int)meta->map.limits.axis[X] * density;
		if (point[i].paint)
		{
			draw_line(meta, point[i], point[x_end]);
			if (line + density < (int)meta->map.limits.axis[Y])
				draw_line(meta, point[i], point[y_end]);
		}
		i += density;
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
