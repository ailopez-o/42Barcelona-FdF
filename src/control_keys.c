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
#include "../lib/miniliblx/minilibx_macos/mlx.h"
#include "../inc/map.h"
#include "../inc/keycodes.h"
#include "../inc/geometry.h"
#include "../inc/control_utils.h"
#include <stdlib.h>


void	control_keys(int key, t_meta *meta)
{
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
		draw_map(meta, FIT);
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
		meta->map.b_dots = !meta->map.b_dots;	
	if (key == KEY_L)
		meta->map.b_lines = !meta->map.b_lines;				
	if (key == KEY_SUM || key == KEY_SUM2)
	{
		if (meta->map.zdivisor > 1)
			meta->map.zdivisor--;			
	}
	if (key == KEY_RES || key == KEY_RES2)
		meta->map.zdivisor++;				
}

int	key_press(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;	
	angle_control(key, meta);
	control_keys(key, meta);
    if (key == KEY_ESC)
	{
		mlx_destroy_window(meta->vars.mlx, meta->vars.win);
		free(meta->map.points);
		exit(0);	
	}
	if (key == KEY_0)
		colorscheme(CARBON, MENU_COLOR, AZUL, BRICK_RED, SAFFRON, &meta->map);
	if (key == KEY_1)
		colorscheme(CARBON, MENU_COLOR, AZUL, BRICK_RED, VERDE, &meta->map);
	if (key == KEY_2)
		colorscheme(WHITE, MENU_COLOR, CARBON, CARBON, CARBON, &meta->map);
	if (key == KEY_3)
		colorscheme(CARBON, MENU_COLOR, WHITE, WHITE, WHITE, &meta->map);
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