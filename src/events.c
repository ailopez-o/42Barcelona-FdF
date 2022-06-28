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

	if (value == 4)
	{
		// Zoom IN
		//meta->map.scale = meta->map.scale + 1;
		//draw_map(meta);
	}
	if (value == 5)
	{
		// Zoom OUT
		//meta->map.scale = meta->map.scale - 1;
		//draw_map(meta);
	}

	return (0);
}

int	keyrelease(int keycode, t_meta *meta)
{
	t_point		dot;
	t_point		start;
	t_point		end;
	int 		i;

	printf("Keycode Press [%d]\n", keycode);	
	if (keycode == KEY_ESC)
	{

		mlx_destroy_window(meta->vars.mlx, meta->vars.win);
		free(meta->map.points);
		free(meta->map.proyect3D);
		free(meta->map.proyect2D);
		exit(0);	
	}
	if (keycode == KEY_1)
		generate_background(meta, 0x000000);
	if (keycode == KEY_2)
	{
		start.axis[x] = 0;
		start.axis[y] = 0;
		start.color = 0x005500;
		end.axis[x] = WINX;
		end.axis[y] = WINY;
		while (end.axis[x] > 0)
		{
			draw_line(meta, start, end);
			end.axis[x] -= 20;
		}
	}
	if (keycode == KEY_3)
	{
		start.axis[x] = WINX;
		start.axis[y] = 0;
		start.color = 0xFF5500;
		end.axis[x] = 0;
		end.axis[y]= WINY;

		while (end.axis[x] < WINX)
		{
			draw_line(meta, start, end);
			end.axis[x] += 20;
		}
	}
	if (keycode == KEY_4)
	{	
		dot.axis[x] = 300;
		dot.axis[y] = 150;
		dot.color = VERDE;
		draw_dot(meta, dot, 10);
	
	}
	if (keycode == KEY_5)
	{
		my_cube(meta);
	}
	if (keycode == KEY_6)
	{
		static int ang;
		ang += 10;
		meta->map.ang[x] = ang;
		meta->map.ang[y] = ang;
		meta->map.ang[z] = 0;
		draw_map(meta);
	}

	if (keycode == KEY_SUM)
	{
		// Zoom IN
		meta->map.scale = meta->map.scale + 1;
		draw_map(meta);
	}
	if (keycode == KEY_RES)
	{
		// Zoom OUT
		if (meta->map.scale > 1)
			meta->map.scale = meta->map.scale - 1;
		draw_map(meta);
	}
	if (meta->bitmap.img)
		draw_bitmap(meta, 0, 0);	
	return(0);
}
