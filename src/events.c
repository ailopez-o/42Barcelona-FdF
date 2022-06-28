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
	t_point		dot;
	t_point		start;
	t_point		end;

	printf("Keycode Press [%d]\n", keycode);
	if (keycode == 53)
		exit(0);
	if (keycode == 18)
		generate_background(meta, 0x000000);
	if (keycode == 19)
	{
		start.axis[x] = 0;
		start.axis[y] = 0;
		start.color = 0x005500;
		end.axis[x] = meta->vars.winX;
		end.axis[y] = meta->vars.winY;
		while (end.axis[x] > 0)
		{
			draw_line(meta, start, end);
			end.axis[x] -= 20;
		}
	}
	if (keycode == 20)
	{
		start.axis[x] = meta->vars.winX;
		start.axis[y] = 0;
		start.color = 0xFF5500;
		end.axis[x] = 0;
		end.axis[y]= meta->vars.winY;

		while (end.axis[x] < meta->vars.winX)
		{
			draw_line(meta, start, end);
			end.axis[x] += 20;
		}
	}
	if (keycode == 21)
	{	
		dot.axis[x] = 300;
		dot.axis[y] = 150;
		dot.color = VERDE;
		draw_dot(meta, dot, 10);
	
	}
	if (keycode == 22)
	{
		my_cube(meta);
	}

	if (meta->bitmap.img)
		draw_bitmap(meta, 0, 0);	
	return(0);
}
