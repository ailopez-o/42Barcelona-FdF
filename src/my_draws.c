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