/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:01:10 by ailopez-          #+#    #+#             */
/*   Updated: 2022/07/06 00:12:08 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"

void	traslate(t_point *points, t_point move, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		points[i].axis[x] = points[i].axis[x] + move.axis[x];
		points[i].axis[y] = points[i].axis[y] + move.axis[y];
		points[i].axis[z] = points[i].axis[z] + move.axis[z];
		i++;
	}
}

int	limits(t_point *points, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (points[i].axis[x] < LIMIT_MINX || \
			points[i].axis[x] > LIMIT_MAXX)
			return (1);
		if (points[i].axis[y] < LIMIT_MINY || \
			points[i].axis[y] > LIMIT_MAXY)
			return (1);
		i++;
	}
	return (0);
}

void	scale(t_point *points, int scale, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		points[i].axis[x] = points[i].axis[x] * scale;
		points[i].axis[y] = points[i].axis[y] * scale;
		points[i].axis[z] = points[i].axis[z] * scale;
		i++;
	}
}

int	fit(t_map *map)
{
	t_point		*proyect;

	proyect = malloc (map->len * sizeof(t_point));
	if (proyect == NULL)
		return (-1);
	rotate_y(map->points, proyect, map->ang[y], map->len);
	rotate_z(proyect, proyect, map->ang[z], map->len);
	orto_proyection (proyect, proyect, map->len);
	//scale (proyect, map->scale, map->len);
	map->scale = 1;
	while (!limits(proyect, map->len))
	{
		map->scale++;
		scale(proyect, map->scale, map->len);
	}
	free (proyect);
	return (1);
}

void	isometric(t_map *map)
{
	map->ang[x] = 30;
	map->ang[y] = 330;
	map->ang[z] = 30;
	map->source.axis[x] = (((WINX - MENU_WIDTH) / 2) + MENU_WIDTH);
	map->source.axis[y] = WINY / 2;
}
