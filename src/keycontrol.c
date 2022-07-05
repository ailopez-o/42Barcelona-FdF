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
		draw_map(meta);
	}
	if (key == KEY_R)
	{
		meta->map.ang[x] = 0;
		meta->map.ang[y] = 0;
		meta->map.ang[z] = 0;
		meta->map.source.axis[x] = WINX/2;
		meta->map.source.axis[y] = WINY/2;
		draw_map(meta);
	}	
	if (key == KEY_F)
	{
		fit(&meta->map);
		printf("Escala [%d]\n", meta->map.len);
		//draw_map(meta);
	}		
    return(0);
}
int	key_release(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	printf("Keycode Release [%d]\n", key);
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 0;
	return(0);
}

int	key_press(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	printf("Keycode Press [%d]\n", key);	
    working_keys(key, meta);
    if (key == KEY_ESC)
	{
		mlx_destroy_window(meta->vars.mlx, meta->vars.win);
		free(meta->map.points);
		exit(0);	
	}
	if (key == KEY_SUM)
	{
		// Zoom IN
		meta->map.scale = meta->map.scale + 1;
		draw_map(meta);
	}
	if (key == KEY_RES)
	{
		// Zoom OUT
		if (meta->map.scale > 1)
			meta->map.scale = meta->map.scale - 1;
		draw_map(meta);
	}
	if (key == KEY_DOWN)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[x] = meta->map.ang[x] + 90;
		else
			meta->map.ang[x] = meta->map.ang[x] + 1;	
		if (meta->map.ang[x] >= 360)
			meta->map.ang[x] = meta->map.ang[x] - 360;
		draw_map(meta);
	}	
	if (key == KEY_UP)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[x] = meta->map.ang[x] - 90;	
		else
			meta->map.ang[x] = meta->map.ang[x] - 1;	
		if (meta->map.ang[x] < 0)
			meta->map.ang[x] = 360 + meta->map.ang[x];
		draw_map(meta);
	}		
	if (key == KEY_LEFT)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[y] = meta->map.ang[y] + 90;
		else
			meta->map.ang[y] = meta->map.ang[y] + 1;	
		if (meta->map.ang[y] >= 360)
			meta->map.ang[y] = meta->map.ang[y] - 360;
		draw_map(meta);
	}	
	if (key == KEY_RIGHT)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[y] = meta->map.ang[y] - 90;
		else
			meta->map.ang[y] = meta->map.ang[y] - 1;	
		if (meta->map.ang[y] < 0)
			meta->map.ang[y] = 360 +  meta->map.ang[y];
		draw_map(meta);
	}	
	if (key == KEY_Q)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[z] = meta->map.ang[z] + 90;
		else		
			meta->map.ang[z] = meta->map.ang[z] + 1;	
		if (meta->map.ang[z] >= 360)
			meta->map.ang[z] = meta->map.ang[z] - 360;
		draw_map(meta);
	}		
	if (key == KEY_W)
	{
		if	(meta->keys.b_keyctrl)
			meta->map.ang[z] = meta->map.ang[z] - 90;
		else				
			meta->map.ang[z] = meta->map.ang[z] - 1;	
		if (meta->map.ang[z] < 0)
			meta->map.ang[z] = 360 +  meta->map.ang[z];			
		draw_map(meta);
	}	
	if (key == KEY_C)
	{
		meta->map.source.axis[x] = WINX/2;
		meta->map.source.axis[y] = WINY/2;
		draw_map(meta);
	}		
	if (key == KEY_I)
	{
		isometric(&meta->map);
		draw_map(meta);
	}			
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 1;
	if (key == KEY_D)
	{
		meta->map.b_dots = !meta->map.b_dots;	
		draw_map(meta);
	}
	if (key == KEY_L)
	{
		meta->map.b_lines = !meta->map.b_lines;				
		draw_map(meta);
	}
	return(0);
}
