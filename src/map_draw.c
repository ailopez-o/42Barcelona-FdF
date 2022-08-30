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
#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/matrix.h"
#include "../inc/geometry.h"
#include "../inc/errors.h"
#include "../inc/map_utils.h"
#include "../inc/draw_utils.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/*
static	void print_coor(t_meta *meta)
{
	t_point	start;
	t_point	end;	

	start.axis[X] = WINX / 2;
	start.axis[Y] = WINY / 2;
	start.axis[Z] = 0;
	start.color = ROJO;
	end.axis[X] = WINX / 2 + 500;
	end.axis[Y] = WINY / 2;
	end.axis[Z] = 0;
	end.color = ROJO;
	draw_line(meta, start, end);
	start.axis[X] = WINX / 2;
	start.axis[Y] = WINY / 2;
	start.axis[Z] = 0;
	start.color = AZUL;
	end.axis[X] = WINX / 2;
	end.axis[Y] = WINY / 2 + 500;
	end.axis[Z] = 0;
	end.color = ROJO;
	draw_line(meta, start, end);

}
*/

static void shadow(t_point *points, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (points[i].axis[Z] < 0)
			points[i].paint = 0;
		else
			points[i].paint = 1;
		i++;
	}
}

/* 
*	Call all the functions to modify the points in the space
*/

static void	parse_map(t_meta *meta, t_point *proyect)
{
	z_division(proyect, meta->map.zdivisor, meta->map.len);
	bending(proyect, meta->map.len, meta->map.brange);
	if (meta->map.b_geo)
		spherize(&meta->map, proyect);
	rotate_x(proyect, proyect, meta->map.ang[X], meta->map.len);
	rotate_y(proyect, proyect, meta->map.ang[Y], meta->map.len);
	rotate_z(proyect, proyect, meta->map.ang[Z], meta->map.len);
	if (meta->map.b_geo)
		shadow (proyect, meta->map.len);	
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
		if (points[i].axis[X] < (MENU_WIDTH + FIT_MARGIN) || \
			points[i].axis[X] > (WINX - FIT_MARGIN))
			return (1);
		if (points[i].axis[Y] < FIT_MARGIN || \
			points[i].axis[Y] > (WINY - FIT_MARGIN))
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
	meta->map.source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	meta->map.source.axis[Y] = WINY / 2;
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
void print_log(t_meta *meta, t_point *points)
{
	int	i;

	i = 0;
	while (i < meta->map.len)
	{
		printf("X[%f]Y[%f]Z[%f] - LAT[%f]LONG[%f] - PRINT[%d]\n", points[i].axis[X], points[i].axis[Y], points[i].axis[Z], points[i].polar[LAT], points[i].polar[LONG], points[i].paint);
		i++;
	}
}
*/

/* 
*	This function draw the proyection of map->points acording all
*	the modifiers (x,y,z, scale..). If fit = 1, will caculate the 
*	scale needed to fit the screen.
*/

int	draw_map(t_meta *meta, int fit)
{
	t_point	*proyect;
	clock_t	t;

	t = clock();
	proyect = malloc (meta->map.len * sizeof(t_point));
	if (proyect == NULL)
		terminate(ERR_MEM);
	meta->map.renders = meta->map.renders + 1;
	generate_background(meta, meta->map.colors.backcolor, \
	meta->map.colors.menucolor);
	//print_coor(meta);
	copy_map(meta->map.points, proyect, meta->map.len);
	parse_map(meta, proyect);
	//printf("RENDER*************************\n");	
	//print_log(meta, proyect);
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
	t = clock() - t;
	meta->map.performance = ((double)t) / CLOCKS_PER_SEC;
	return (1);
}
