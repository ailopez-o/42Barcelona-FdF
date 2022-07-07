/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:01:24 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/29 16:01:28 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"

int working_keys(int key, t_meta *meta)
{
	if (key == KEY_6)
	{
		static int ang;
		ang += 1;
		meta->map.ang[x] = ang;
		meta->map.ang[y] = ang;
		meta->map.ang[z] = 0;
	}
	if (key == KEY_R)
	{
		meta->map.ang[x] = 0;
		meta->map.ang[y] = 0;
		meta->map.ang[z] = 0;
		meta->map.source.axis[x] = XCENTER;
		meta->map.source.axis[y] = YCENTER;		
		draw_map(meta, FIT);
	}	
	if (key == KEY_F)
	{
		draw_map(meta, FIT);
	}		
	draw_map(meta, FREE);
    return(0);
}
int	key_release(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 0;
	return(0);
}

int	key_press(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;	
    working_keys(key, meta);
    if (key == KEY_ESC)
	{
		mlx_destroy_window(meta->vars.mlx, meta->vars.win);
		free(meta->map.points);
		exit(0);	
	}
	if (key == KEY_DOWN)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[x] = meta->map.ang[x] + 90;
		else
			meta->map.ang[x] = meta->map.ang[x] + 1;	
		if (meta->map.ang[x] >= 360)
			meta->map.ang[x] = meta->map.ang[x] - 360;
	}	
	if (key == KEY_UP)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[x] = meta->map.ang[x] - 90;	
		else
			meta->map.ang[x] = meta->map.ang[x] - 1;	
		if (meta->map.ang[x] < 0)
			meta->map.ang[x] = 360 + meta->map.ang[x];
	}		
	if (key == KEY_LEFT)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[y] = meta->map.ang[y] + 90;
		else
			meta->map.ang[y] = meta->map.ang[y] + 1;	
		if (meta->map.ang[y] >= 360)
			meta->map.ang[y] = meta->map.ang[y] - 360;
	}	
	if (key == KEY_RIGHT)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[y] = meta->map.ang[y] - 90;
		else
			meta->map.ang[y] = meta->map.ang[y] - 1;	
		if (meta->map.ang[y] < 0)
			meta->map.ang[y] = 360 +  meta->map.ang[y];
	}	
	if (key == KEY_Q)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[z] = meta->map.ang[z] + 90;
		else		
			meta->map.ang[z] = meta->map.ang[z] + 1;	
		if (meta->map.ang[z] >= 360)
			meta->map.ang[z] = meta->map.ang[z] - 360;
	}		
	if (key == KEY_W)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[z] = meta->map.ang[z] - 90;
		else				
			meta->map.ang[z] = meta->map.ang[z] - 1;	
		if (meta->map.ang[z] < 0)
			meta->map.ang[z] = 360 +  meta->map.ang[z];			
	}	
	if (key == KEY_C)
	{
		meta->map.source.axis[x] = XCENTER;
		meta->map.source.axis[y] = YCENTER;
	}		
	if (key == KEY_I)
	{
		isometric(&meta->map);
		draw_map(meta, FIT);
	}			
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 1;
	if (key == KEY_D)
	{
		meta->map.b_dots = !meta->map.b_dots;	
	}
	if (key == KEY_L)
	{
		meta->map.b_lines = !meta->map.b_lines;				
	}
	if (key == KEY_SUM || key == KEY_SUM2)
	{
		if (meta->map.zdivisor > 1)
			meta->map.zdivisor--;			
	}
	if (key == KEY_RES || key == KEY_RES2)
	{
		meta->map.zdivisor++;				
	}	
	draw_map(meta, FREE);
	return(0);
}
