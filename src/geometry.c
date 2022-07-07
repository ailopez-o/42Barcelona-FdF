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
/*
int	fit(t_map *map)
{
	t_point		*proyect;

	proyect = malloc (map->len * sizeof(t_point));
	if (proyect == NULL)
		return (-1);

		copy_map(map->points, proyect, map->len);
		z_division(proyect, map->zdivisor, map->len);
		rotate_x(proyect, proyect, map->ang[x], map->len);
		rotate_y(proyect, proyect, map->ang[y], map->len);
		rotate_z(proyect, proyect, map->ang[z], map->len);	
		orto_proyection (proyect, proyect, map->len);
		map->source.axis[x] = XCENTER;
		map->source.axis[y] = YCENTER;	
		map->source.axis[z] = 0;
		map->scale = 2;
		scale (proyect, map->scale, map->len);
		traslate(proyect, map->source, map->len);
	while (!limits(proyect, map->len))	
	{
		copy_map(map->points, proyect, map->len);
		z_division(proyect, map->zdivisor, map->len);
		rotate_x(proyect, proyect, map->ang[x], map->len);
		rotate_y(proyect, proyect, map->ang[y], map->len);
		rotate_z(proyect, proyect, map->ang[z], map->len);	
		orto_proyection (proyect, proyect, map->len);
		map->source.axis[x] = XCENTER;
		map->source.axis[y] = YCENTER;	
		map->source.axis[z] = 0;
		scale (proyect, map->scale, map->len);
		traslate(proyect, map->source, map->len);
		map->scale++;
	}
	free (proyect);
	return (1);
}
*/
void	isometric(t_map *map)
{
	map->ang[x] = 30;
	map->ang[y] = 330;
	map->ang[z] = 30;
	map->source.axis[x] = XCENTER;
	map->source.axis[y] = YCENTER;
}
