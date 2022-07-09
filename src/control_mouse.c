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
		angle(&meta->map.ang[x], (int)meta->keys.last_clickL.axis[y] - Y);
		angle(&meta->map.ang[y], (int)meta->keys.last_clickL.axis[x] - X);
		meta->keys.last_clickL.axis[x] = X;
		meta->keys.last_clickL.axis[y] = Y;
		draw_map(meta, FREE);
	}
	if (meta->keys.b_mouseR)
	{
		meta->map.source.axis[x] -= ((int)meta->keys.last_clickR.axis[x] - X);
		meta->map.source.axis[y] -= ((int)meta->keys.last_clickR.axis[y] - Y);
		meta->map.source.axis[z] = 0;
		meta->keys.last_clickR.axis[x] = X;
		meta->keys.last_clickR.axis[y] = Y;
		draw_map(meta, FREE);
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
		if (meta->map.scale > 2)
			meta->map.scale = meta->map.scale / 1.5;
	}
	if (button == 5)
		meta->map.scale = meta->map.scale * 1.5;
	draw_map(meta, FREE);
	return (0);
}
