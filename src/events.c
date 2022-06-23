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

	line.beginX = 0;
	line.beginY = 0;
	line.begincolor = 0x005500;
	line.endX = meta->vars.winX;
	line.endY = meta->vars.winY;

	printf("Keycode Press [%d]\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == 18)
		generate_background(meta, 0x000000);
	if (keycode == 19)
	{
		line.beginX = 0;
		line.beginY = 0;
		line.begincolor = 0x005500;
		line.endX = meta->vars.winX;
		line.endY = meta->vars.winY;
		while (line.endX > 0)
		{
			draw_line(meta, line);
			line.endX -= 20;
		}
	}
	if (keycode == 20)
	{
		line.beginX = meta->vars.winX;
		line.beginY = 0;
		line.endX = 0;
		line.endY = meta->vars.winY;
		line.begincolor = 0xFF5500;

		while (line.endX < meta->vars.winX)
		{
			draw_line(meta, line);
			line.endX += 20;
		}
	
	}
	if (keycode == 21)
		generate_background(meta, 0xFF4534);
	if (meta->bitmap.img)
		draw_bitmap(meta, 0, 0);	
	return(0);
}
