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
#include "../inc/defines.h"
#include <math.h>

/*
*	Iterates all the points and add the "move" traslation
*/

void	traslate(t_point *points, t_point move, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		points[i].axis[X] = points[i].axis[X] + move.axis[X];
		points[i].axis[Y] = points[i].axis[Y] + move.axis[Y];
		points[i].axis[Z] = points[i].axis[Z] + move.axis[Z];
		i++;
	}
}

/*
*	Iterates all the points and multiply by scale
*/

void	scale(t_point *points, int scale, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		points[i].axis[X] = points[i].axis[X] * scale;
		points[i].axis[Y] = points[i].axis[Y] * scale;
		points[i].axis[Z] = points[i].axis[Z] * scale;
		i++;
	}
}

/*
*	Set the values to draw ISOMETRIC view
*/

void	isometric(t_map *map)
{
	map->ang[X] = 30;
	map->ang[Y] = 330;
	map->ang[Z] = 30;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
}

/*
*	Set the values to draw PARALLEL view
*/

void	parallel(t_map *map)
{
	map->ang[X] = 90;
	map->ang[Y] = 0;
	map->ang[Z] = 0;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
}

/*
*	Iterate all the point to move the z value depending the range 
*	and the x and y position
*/

void	bending(t_point *points, int len, float range)
{
	int		i;
	float	vv;

	i = 0;
	while (i < len)
	{
		vv = ((points[i].axis[X] * points[i].axis[X]) * (range)) + \
		(points[i].axis[Y] * points[i].axis[Y]) * (range);
		points[i].axis[Z] = points[i].axis[Z] - vv;
		i++;
	}
}

void 	spherize(t_map *map, t_point *points)
{
	int i;

	i = 0;
	while (i < map->len)
	{
		points[i].axis[X] = (map->radius + points[i].axis[Z]) * cos(points[i].polar[LONG]) * sin(points[i].polar[LAT]);
		points[i].axis[Y] = (map->radius + points[i].axis[Z]) * sin(points[i].polar[LONG]) * sin(points[i].polar[LAT]);
		points[i].axis[Z] = (map->radius + points[i].axis[Z]) * cos(points[i].polar[LAT]);	
		i++;
	}


}
/*
void 	spherize(t_map *map, t_point *points)
{
	int		i;
	float 	steps_x;
	float	steps_y;
	int 	radius;

	radius = map->limits.axis[X] / (M_PI *2);
	steps_x = (360 / map->limits.axis[X]) *  (M_PI / 180);
	steps_y = (180 / map->limits.axis[Y]) *  (M_PI / 180);


	i = 0;
	while (i < map->len)
	{
		if ((points[i].axis[X] > -(map->limits.axis[X] / 4)) && (points[i].axis[X] < (map->limits.axis[X] / 4 )))
			points[i].axis[Z] =  radius * cos(points[i].axis[X] * steps_x) * cos(points[i].axis[Y] * steps_y);
		if (points[i].axis[X] < -(map->limits.axis[X] / 4))
		{	
			//points[i].axis[Z] = (radius * cos(points[i].axis[X] * steps_x) * cos(points[i].axis[Y] * steps_y));
			points[i].axis[X] = - (points[i].axis[X] + (map->limits.axis[X] / 2));
			points[i].axis[Z] = - radius * cos(points[i].axis[X] * steps_x) * cos(points[i].axis[Y] * steps_y);
		
		}
		if (points[i].axis[X] > (map->limits.axis[X] / 4))
		{	
			//points[i].axis[Z] = (radius * cos(points[i].axis[X] * steps_x) * cos(points[i].axis[Y] * steps_y));
			points[i].axis[X] = - (points[i].axis[X] - (map->limits.axis[X] / 2));
			points[i].axis[Z] = - radius * cos(points[i].axis[X] * steps_x) * cos(points[i].axis[Y] * steps_y);
		
		}
		//points[i].axis[Y] = points[i].axis[Y] + (points[i].axis[Y] * cos(points[i].axis[Y] * steps_y));
		i++;
	}
}
*/

