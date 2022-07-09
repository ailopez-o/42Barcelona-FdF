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
#include "../inc/map.h"

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

void	isometric(t_map *map)
{
	map->ang[x] = 30;
	map->ang[y] = 330;
	map->ang[z] = 30;
	map->source.axis[x] = XCENTER;
	map->source.axis[y] = YCENTER;
}
