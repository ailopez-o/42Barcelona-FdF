/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:25:47 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 13:25:52 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/miniliblx/minilibx_macos/mlx.h"
#include "../inc/map.h"
#include "../inc/matrix.h"
#include "../inc/geometry.h"
#include "../inc/errors.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

static void	parse_map(t_meta *meta, t_point *proyect)
{
	z_division(proyect, meta->map.zdivisor, meta->map.len);
	bending(proyect, meta->map.len, meta->map.brange);
	rotate_x(proyect, proyect, meta->map.ang[X], meta->map.len);
	rotate_y(proyect, proyect, meta->map.ang[Y], meta->map.len);
	rotate_z(proyect, proyect, meta->map.ang[Z], meta->map.len);
	orto_proyection (proyect, proyect, meta->map.len);
	scale (proyect, meta->map.scale, meta->map.len);
	traslate(proyect, meta->map.source, meta->map.len);
}

/* 
*	This function checks if any point is out of the limits of the screen
*/

static int	limits(t_point *points, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (points[i].axis[X] < LIMIT_MINX || \
			points[i].axis[X] > LIMIT_MAXX)
			return (1);
		if (points[i].axis[Y] < LIMIT_MINY || \
			points[i].axis[Y] > LIMIT_MAXY)
			return (1);
		i++;
	}
	return (0);
}

/* 
*	This function copy len points of the array from src to dst
*/

static void	copy_map(t_point *src, t_point *dst, int len)
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
*	This function iterate n times until get the scale needed
*	to fit the screen.
*/

static void	go_fit(t_meta *meta, t_point *proyect)
{
	meta->map.source.axis[X] = XCENTER;
	meta->map.source.axis[Y] = YCENTER;
	meta->map.source.axis[Z] = 0;
	meta->map.scale = 1;
	copy_map(meta->map.points, proyect, meta->map.len);
	parse_map(meta, proyect);
	while (!(limits(proyect, meta->map.len)))
	{
		copy_map(meta->map.points, proyect, meta->map.len);
		parse_map(meta, proyect);
		meta->map.scale = meta->map.scale + 0.2;
	}
}

/* 
*	This function draw the proyection of map->points acording all
*	the modifiers (x,y,z, scale..). If fit = 1, will caculate the 
*	scale needed to fit the screen.
*/

int	draw_map(t_meta *meta, int fit)
{
	t_point		*proyect;



    // Calculate the time taken by fun()
    clock_t t;
    t = clock();
	// *******************

	proyect = malloc (meta->map.len * sizeof(t_point));
	if (proyect == NULL)
		terminate(ERR_MEM);
	meta->map.renders = meta->map.renders + 1;
	generate_background(meta, meta->map.colors.backcolor, \
	meta->map.colors.menucolor);
	copy_map(meta->map.points, proyect, meta->map.len);
	parse_map(meta, proyect);
	if (fit)
		go_fit(meta, proyect);
	if (meta->map.b_lines)
		wired(meta, proyect);
	if (meta->map.b_dots)
		doted(meta, proyect);
	mlx_put_image_to_window(meta->vars.mlx, meta->vars.win, \
	meta->bitmap.img, 0, 0);
	draw_menu(meta);
	free (proyect);

	// *******************
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("Performance [%f]\n", time_taken);	
	// *******************
	return (1);
}
