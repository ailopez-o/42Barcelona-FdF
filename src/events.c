/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:51:19 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/22 13:51:24 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"

int	mouse_hook(int value, t_meta *meta)
{
	printf("Mouse Press [%d]\n", value);
	return (0);
}

int	keyrelease(int keycode, t_meta *meta)
{
	t_line	line;
	t_coord	dot;

	printf("Keycode Press [%d]\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == 18)
		generate_background(meta, 0x000000);
	if (keycode == 19)
	{
		line.start.X = 0;
		line.start.Y = 0;
		line.start.color = 0x005500;
		line.end.X = meta->vars.winX;
		line.end.Y = meta->vars.winY;
		while (line.end.X > 0)
		{
			draw_line(meta, line);
			line.end.X -= 20;
		}
	}
	if (keycode == 20)
	{
		line.start.X = meta->vars.winX;
		line.start.Y = 0;
		line.start.color = 0xFF5500;
		line.end.X = 0;
		line.end.Y = meta->vars.winY;

		while (line.end.X < meta->vars.winX)
		{
			draw_line(meta, line);
			line.end.X += 20;
		}
	}
	if (keycode == 21)
	{	
		dot.X = 300;
		dot.Y = 150;
		dot.color = VERDE;
		draw_dot(meta, dot, 10);
	
	}
	if (meta->bitmap.img)
		draw_bitmap(meta, 0, 0);	
	return(0);
}
