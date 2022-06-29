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
		return(0);
	printf("Mouse Press [%d][%d]\n", X,Y);
	if (meta->b_mouseL)
	{
		printf("LastClickL [%d][%d] - Currect Click [%d][%d] - Increment [%d][%d]\n", (int)meta->last_clickL.axis[x], (int)meta->last_clickL.axis[y], X,Y, (int)(meta->last_clickL.axis[x] - X)/4, (int)(meta->last_clickL.axis[y] - X)/4);
		meta->map.ang[x] += ((int)meta->last_clickL.axis[y] - Y);
		meta->map.ang[y] += ((int)meta->last_clickL.axis[x] - X);
		if (meta->map.ang[x] < 0)
			meta->map.ang[x] = 360 + meta->map.ang[x];
		if (meta->map.ang[x] > 360)
			meta->map.ang[x] = meta->map.ang[x] - 360;	
		if (meta->map.ang[y] < 0)
			meta->map.ang[y] = 360 + meta->map.ang[y];
		if (meta->map.ang[y] > 360)
			meta->map.ang[y] = meta->map.ang[y] - 360;	
		meta->last_clickL.axis[x] = X;
		meta->last_clickL.axis[y] = Y;			
		draw_map(meta);
	}
	if (meta->b_mouseR)
	{
		printf("LastClickR [%d][%d] - Currect Click [%d][%d] - Increment [%d][%d]\n", (int)meta->last_clickR.axis[x], (int)meta->last_clickR.axis[y], X,Y, (int)(meta->last_clickR.axis[x] - X)/50, (int)(meta->last_clickR.axis[y] - X)/50);	
		meta->map.source.axis[x] -= ((int)meta->last_clickR.axis[x] - X);
		meta->map.source.axis[y] -= ((int)meta->last_clickR.axis[y] - Y);
		meta->map.source.axis[z] = 0;
		//traslate(meta->map.proyect3D, meta->map.source, meta->map.len);
		meta->last_clickR.axis[x] = X;
		meta->last_clickR.axis[y] = Y;
		draw_map(meta);
	}
	return(0);
}

int	mouse_release(int button, int X, int Y, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	printf("Mouse Release[%d] - [%d][%d]\n", button, X,Y);
	if (button == 1)
		meta->b_mouseL = 0;
	if (button == 2)
		meta->b_mouseR = 0;		
	return(0);
}

int	mouse_press(int button, int X, int Y, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	printf("Mouse Press[%d] - [%d][%d]\n", button, X,Y);

	if (button == 1)
	{
		meta->b_mouseL = 1;
		meta->last_clickL.axis[x] = X;
		meta->last_clickL.axis[y] = Y;
	}
	if (button == 2)
	{
		meta->b_mouseR = 1;
		meta->last_clickR.axis[x] = X;
		meta->last_clickR.axis[y] = Y;
	}	
	if (button == 4)
	{
		// Zoom IN
		meta->map.scale = meta->map.scale + 1;
		draw_map(meta);
	}
	if (button == 5)
	{
		// Zoom OUT
		if (meta->map.scale > 1)
			meta->map.scale = meta->map.scale - 1;
		draw_map(meta);
	}
	return (0);

}
