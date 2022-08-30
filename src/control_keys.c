/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:01:24 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/29 16:01:28 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/miniliblx/minilibx_macos/mlx.h"
#include "../inc/defines.h"
#include "../inc/map.h"
#include "../inc/keycodes.h"
#include "../inc/geometry.h"
#include "../inc/control_utils.h"
#include "../inc/map_utils.h"
#include <stdlib.h>

//Testting branch

/* 
*	This function handle some key press events
*/

void	control_keys2(int key, t_meta *meta)
{
	if (key == KEY_D)
		meta->map.b_dots = !meta->map.b_dots;
	if (key == KEY_L)
		meta->map.b_lines = !meta->map.b_lines;
	if (key == KEY_X)
		meta->map.b_pluslines = !meta->map.b_pluslines;
	if (key == KEY_G)
		meta->map.b_geo = !meta->map.b_geo;		
	if (key == KEY_F)
		draw_map(meta, FIT);
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 1;
	if (key == KEY_B)
	{
		if (meta->keys.b_keyctrl)
			meta->map.brange -= 0.0001;
		else
			meta->map.brange += 0.0001;
	}
	if (key == KEY_SUM || key == KEY_SUM2)
	{
		if (meta->keys.b_keyctrl)
			meta->map.scale = meta->map.scale * 1.5;
		if (meta->map.zdivisor > 1)
			meta->map.zdivisor--;
	}
	if (key == KEY_RES || key == KEY_RES2)
	{
		if (meta->keys.b_keyctrl)
			meta->map.scale = meta->map.scale / 1.5;
		meta->map.zdivisor++;
	}
}

/* 
*	This function handle some key press events
*/

void	control_keys1(int key, t_meta *meta)
{
	if (key == KEY_ESC)
		terminate_program(meta);
	if (key == KEY_R)
	{
		map_ini(&meta->map, 0);
		meta->map.proportion = meta->map.limits.axis[Z] / meta->map.limits.axis[X];
		if (meta->map.proportion > 0.5)
			meta->map.zdivisor = meta->map.proportion * 30;		
		colorize(&meta->map);
		draw_map(meta, FIT);
	}	
	if (key == KEY_C)
	{
		meta->map.source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
		meta->map.source.axis[Y] = WINY / 2;
	}		
	if (key == KEY_I)
	{
		isometric(&meta->map);
		draw_map(meta, FIT);
	}			
	if (key == KEY_P)
	{
		parallel(&meta->map);
		draw_map(meta, FIT);
	}		
}

/* 
*	This function handle the colorscheme dependig the key pressed
*/

void	control_colorscheme(int key, t_map *map)
{
	if (key == KEY_1)
	{
		map->colors.backcolor = CARBON;
		map->colors.bottomcolor = AZUL;
		map->colors.topcolor = BRICK_RED;
		map->colors.groundcolor = SAFFRON;
		colorize(map);
	}
	if (key == KEY_2)
	{
		map->colors.backcolor = WHITE;
		map->colors.bottomcolor = CARBON;
		map->colors.topcolor = CARBON;
		map->colors.groundcolor = CARBON;
		colorize(map);
	}
	if (key == KEY_3)
	{
		map->colors.backcolor = CARBON;
		map->colors.bottomcolor = WHITE;
		map->colors.topcolor = WHITE;
		map->colors.groundcolor = WHITE;
		colorize(map);
	}
	if (key == KEY_4)
	{
		map->colors.backcolor = CARBON;
		map->colors.bottomcolor = AZUL;
		map->colors.topcolor = ROJO;
		map->colors.groundcolor = VERDE;
		colorize(map);
	}	
}

/* 
*	This function handle when a key is pressed
*/

int	key_press(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	angle_control(key, meta);
	control_keys1(key, meta);
	control_keys2(key, meta);
	control_colorscheme(key, &meta->map);
	draw_map(meta, FREE);
	return (0);
}

/* 
*	This function handle when a key is relased
*/

int	key_release(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 0;
	return (0);
}
