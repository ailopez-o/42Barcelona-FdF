/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:09:51 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/10 21:09:56 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/miniliblx/minilibx_macos/mlx.h"
#include "../inc/defines.h"
#include "../inc/utils.h"
#include "../inc/draw_utils.h"
#include <math.h>
#include <stdlib.h>

/*
*	This function fills 4 bytes of the given address whith the values of colors
*	depending the andian
*      endian = 1 --> Most significant (Alpha) byte first
*      endian = 0 --> Least significant (Blue) byte first
*/

void	set_color(char *buffer, int endian, int color, int alpha)
{
	if (endian == 1)
	{
		buffer[0] = alpha;
		buffer[1] = (color >> 16) & 0xFF;
		buffer[2] = (color >> 8) & 0xFF;
		buffer[3] = (color) & 0xFF;
	}
	else
	{
		buffer[0] = (color) & 0xFF;
		buffer[1] = (color >> 8) & 0xFF;
		buffer[2] = (color >> 16) & 0xFF;
		buffer[3] = alpha;
	}
}

/*
*	This function calculate the position of the pixel in the img array:
*		array_pixe_position = pixel.axis[y] * WINX * 4 + 4 * pixel.axis[y]
*	and fill the 4 colorbytes calling the set_color function
*/

int	my_putpixel(t_meta *meta, t_point pixel)
{
	int	mypixel;
	int	alpha;

	alpha = 0;
	if (pixel.axis[X] < MENU_WIDTH)
		alpha = -10;
	if (pixel.axis[X] >= WINX || pixel.axis[Y] >= WINY || \
		pixel.axis[X] < 0 || pixel.axis[Y] < 0)
		return (-1);
	mypixel = ((int)pixel.axis[Y] * WINX * 4) + ((int)pixel.axis[X] * 4);
	if (meta->bitmap.bitxpixel != 32)
		pixel.color = mlx_get_color_value(meta->vars.mlx, pixel.color);
	set_color(&meta->bitmap.buffer[mypixel], \
		meta->bitmap.endian, pixel.color, alpha);
	return (0);
}

/*
*	This function set the color value to 32bits value in case of need
*/

int	get_color(t_meta *meta, int color)
{	
	if (meta->bitmap.bitxpixel != 32)
		color = mlx_get_color_value(meta->vars.mlx, color);
	return (color);
}

/*
*	This function generate all the pixel colors and fill the img array propertly
*/

void	generate_background(t_meta *meta, int backcolor, int menucolor)
{
	int	axis[2];
	int	pixel;
	int	color;

	backcolor = get_color(meta, backcolor);
	menucolor = get_color(meta, menucolor);
	axis[X] = 0;
	axis[Y] = 0;
	while (axis[Y] < WINY)
	{
		while (axis[X] < WINX)
		{
			if (axis[X] < MENU_WIDTH)
				color = menucolor;
			else
				color = backcolor;
			pixel = (axis[Y] * meta->bitmap.lines) + (axis[X] * 4);
			set_color(&meta->bitmap.buffer[pixel], \
						meta->bitmap.endian, color, 1);
			axis[X]++;
		}
		axis[Y]++;
		axis[X] = 0;
	}
}

void	generate_stars(t_meta *meta)
{
	int		i;
	t_point	star;
	int		lim_x[2];
	int		lim_y[2];

	if (meta->map.b_geo == 0)
		return ;
	lim_x[0] = meta->map.source.axis[X] - (meta->map.radius * meta->map.scale);
	lim_x[1] = meta->map.source.axis[X] + (meta->map.radius * meta->map.scale);
	lim_y[0] = meta->map.source.axis[Y] - (meta->map.radius * meta->map.scale);
	lim_y[1] = meta->map.source.axis[Y] + (meta->map.radius * meta->map.scale);
	i = 0;
	while (i < 200)
	{
		star.axis[X] = rand() % WINX;
		star.axis[Y] = rand() % WINY;
		star.color = WHITE;
		if ((star.axis[X] < lim_x[0] || star.axis[X] > lim_x[1]) \
		|| ((star.axis[Y]) < lim_y[0] || star.axis[Y] > lim_y[1]))
			draw_dot(meta, star, 2);
		i++;
	}
}
