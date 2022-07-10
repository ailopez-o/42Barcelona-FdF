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
#include "../inc/map.h"
#include "../inc/keycodes.h"
#include "../inc/geometry.h"
#include "../inc/control_utils.h"
#include <stdlib.h>

void	control_keys2(int key, t_meta *meta)
{
	if (key == KEY_D)
		meta->map.b_dots = !meta->map.b_dots;
	if (key == KEY_L)
		meta->map.b_lines = !meta->map.b_lines;
	if (key == KEY_B)
	{
		if (meta->keys.b_keyctrl)
			meta->map.brange -= 0.0001;
		else
			meta->map.brange += 0.0001;
	}
	if (key == KEY_SUM || key == KEY_SUM2)
	{
		if (meta->map.zdivisor > 1)
			meta->map.zdivisor--;
	}
	if (key == KEY_RES || key == KEY_RES2)
		meta->map.zdivisor++;
}

void	control_keys1(int key, t_meta *meta)
{
	if (key == KEY_ESC)
		terminate_program(meta);
	if (key == KEY_R)
	{
		map_ini(&meta->map);
		draw_map(meta, FIT);
	}	
	if (key == KEY_F)
		draw_map(meta, FIT);
	if (key == KEY_C)
	{
		meta->map.source.axis[X] = XCENTER;
		meta->map.source.axis[Y] = YCENTER;
	}		
	if (key == KEY_I)
	{
		isometric(&meta->map);
		draw_map(meta, FIT);
	}			
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 1;
}

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
}

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

int	key_release(int key, void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	if (key == KEY_CMD)
		meta->keys.b_keyctrl = 0;
	return (0);
}
