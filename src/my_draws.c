/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_draws.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:41:26 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/22 13:51:34 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"
/*
int 	discoteque(t_vars *vars, int sizex, int sizey, int color)
{
	int colorize;
	int startx;
	int starty;

	startx = sizex;
	starty = sizey;
	for (int i = 0; i < 100; i++)
	{
		colorize = color;
		startx = 1920;
		starty = 1080;
		while (startx > 0)
		{
			draw_line_fast(vars, startx, starty, 0, 0, colorize);
			startx = startx - 40;
			colorize = colorize - 0x000020;
		}
		colorize = color;
		startx = 0;
		starty = 1080;
		while (startx < 1920)
		{
			draw_line_fast(vars, startx, starty, 1920, 0, colorize);
			startx = startx + 40;
			colorize = colorize - 0x000020;
		}
	}
	return (0);
}

int		drawing(t_vars *vars, int sizex, int sizey, int color)
{

	draw_line(vars, sizex, sizey, 1920, 1080, color);	
	sleep(1);
	sizex += 50;
	sizey += 50;	
	draw_line(vars, sizex, sizey, 1920, 1080, color);		
	//sleep(1);
	sizex += 50;
	sizey += 50;	
	draw_line(vars, sizex, sizey, 1920, 1080, color);	
	//sleep(1);
	sizex += 50;
	sizey += 50;	
	draw_line(vars, sizex, sizey, 1920, 1080, color);	
	return(0);	
}
*/
void load_cube(t_point *cube)
{

	for (int i = 0; i<8; i++)
		cube[i].color= FUCSIA;

	cube[0].axis[x] = 10;
	cube[0].axis[y] = 10;
	cube[0].axis[z] = -5;

	cube[1].axis[x] = 20;
	cube[1].axis[y] = 10;
	cube[1].axis[z] = -5;

	cube[2].axis[x] = 10;
	cube[2].axis[y] = 20;
	cube[2].axis[z] = -5;

	cube[3].axis[x] = 20;
	cube[3].axis[y] = 20;
	cube[3].axis[z] = -5;

	cube[4].axis[x] = 10;
	cube[4].axis[y] = 10;
	cube[4].axis[z] = 5;	

	cube[5].axis[x] = 20;
	cube[5].axis[y] = 10;
	cube[5].axis[z] = 5;

	cube[6].axis[x] = 10;
	cube[6].axis[y] = 20;
	cube[6].axis[z] = 5;

	cube[7].axis[x] = 10;
	cube[7].axis[y] = 10;
	cube[7].axis[z] = 5;	
}

void	my_cube(t_meta *meta)
{
	int			i;
	t_point		cube[8];
	t_point		proyection2D[8];
	t_point		rotated3D[8];
	t_point		traslated[8];
	t_point		move;
	static		float	ang = 1;
	
	load_cube(cube);
	ang = ang + 10;
	rotate_z(cube, rotated3D, ang, 8);
	orto_proyection (rotated3D, proyection2D, 8);
	//orto_proyection (cube, proyection2D, 8);	
	move.axis[x] += 100;
	move.axis[y] += 100;
	traslate(proyection2D, move, 8);
	i = 0;
	while (i < 8)
	{
		proyection2D[i].color = VERDE;
		draw_dot(meta, proyection2D[i], 1);
		printf ("[%f, %f, %f] - [%f, %f, %f] - %x\n", cube[i].axis[x], cube[i].axis[y], cube[i].axis[z], proyection2D[i].axis[x], proyection2D[i].axis[y], proyection2D[i].axis[z], proyection2D->color);
		i++;
	}
	ang = ang - 0.1;
}