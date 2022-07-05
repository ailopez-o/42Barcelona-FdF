/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:04:04 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/29 16:04:07 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"

int	mouse_move(int X, int Y, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	if (X > WINX || X < 0 || Y > WINY || Y < 0)
		return (0);
	if (meta->keys.b_mouseL)
	{
		meta->map.ang[x] += ((int)meta->keys.last_clickL.axis[y] - Y);
		meta->map.ang[y] += ((int)meta->keys.last_clickL.axis[x] - X);
		if (meta->map.ang[x] < 0)
			meta->map.ang[x] = 360 + meta->map.ang[x];
		if (meta->map.ang[x] > 360)
			meta->map.ang[x] = meta->map.ang[x] - 360;
		if (meta->map.ang[y] < 0)
			meta->map.ang[y] = 360 + meta->map.ang[y];
		if (meta->map.ang[y] > 360)
			meta->map.ang[y] = meta->map.ang[y] - 360;
		meta->keys.last_clickL.axis[x] = X;
		meta->keys.last_clickL.axis[y] = Y;
		draw_map(meta);
	}
	if (meta->keys.b_mouseR)
	{
		meta->map.source.axis[x] -= ((int)meta->keys.last_clickR.axis[x] - X);
		meta->map.source.axis[y] -= ((int)meta->keys.last_clickR.axis[y] - Y);
		meta->map.source.axis[z] = 0;
		meta->keys.last_clickR.axis[x] = X;
		meta->keys.last_clickR.axis[y] = Y;
		draw_map(meta);
	}
	return (0);
}

int	mouse_release(int button, int X, int Y, void *param)
{
	t_meta	*meta;

	X++;
	Y++;
	meta = (t_meta *)param;
	if (button == 1)
		meta->keys.b_mouseL = 0;
	if (button == 2)
		meta->keys.b_mouseR = 0;
	return (0);
}

int	mouse_press(int button, int X, int Y, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	if (button == 1)
	{
		meta->keys.b_mouseL = 1;
		meta->keys.last_clickL.axis[x] = X;
		meta->keys.last_clickL.axis[y] = Y;
	}
	if (button == 2)
	{
		meta->keys.b_mouseR = 1;
		meta->keys.last_clickR.axis[x] = X;
		meta->keys.last_clickR.axis[y] = Y;
	}	
	if (button == 4)
	{
		meta->map.scale = meta->map.scale * 1.1;
		draw_map(meta);
	}
	if (button == 5)
	{
		if (meta->map.scale > 1)
			meta->map.scale = meta->map.scale / 1.1;
		draw_map(meta);
	}
	return (0);
}
