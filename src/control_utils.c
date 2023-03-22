/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:45:09 by aitorlope         #+#    #+#             */
/*   Updated: 2023/03/22 01:20:54 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniliblx/minilibx_macos/mlx.h"
#include "../lib/libft/libft.h"
#include "../inc/defines.h"
#include "../inc/keycodes.h"
#include "../inc/map.h"
#include "../inc/map_utils.h"
#include <errno.h>

/* 
*	This function increment the ang value by value, checking is under the limits
*/

void	angle(float *ang, float value)
{
	*ang += value;
	if (*ang < 0)
			*ang = 360 + *ang;
	if (*ang >= 360)
			*ang = *ang - 360;
}

/* 
*	This function add grades to the control structure depends the key pressed
*/

void	angle_control(int key, t_meta *meta)
{
	int	ang;

	ang = 1;
	if (meta->keys.b_keyctrl)
		ang = 90;
	if (key == KEY_DOWN)
		angle(&meta->map.ang[X], ang);
	if (key == KEY_UP)
		angle(&meta->map.ang[X], -ang);
	if (key == KEY_LEFT)
		angle(&meta->map.ang[Y], ang);
	if (key == KEY_RIGHT)
		angle(&meta->map.ang[Y], -ang);
	if (key == KEY_Q)
		angle(&meta->map.ang[Z], ang);
	if (key == KEY_W)
		angle(&meta->map.ang[Z], -ang);
}

/* 
*	This function handle the program shut down
*/

int	terminate_program(void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	mlx_destroy_window(meta->vars.mlx, meta->vars.win);
	free(meta->map.points);
	exit(0);
}

/* 
*	This function handle the program shut down when a error happends
*/

void	terminate(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

/* 
*	This function handle the colorscheme dependig the key pressed
*/

void	control_colorscheme(int key, t_map *map)
{
	map->colors.backcolor = CARBON;
	map->colors.bottomcolor = AZUL;
	map->colors.topcolor = BRICK_RED;
	map->colors.groundcolor = SAFFRON;
	if (key == KEY_2)
	{
		map->colors.backcolor = WHITE;
		map->colors.bottomcolor = CARBON;
		map->colors.topcolor = CARBON;
		map->colors.groundcolor = CARBON;
	}
	if (key == KEY_3)
	{
		map->colors.bottomcolor = WHITE;
		map->colors.topcolor = WHITE;
		map->colors.groundcolor = WHITE;
	}
	if (key == KEY_4)
	{
		map->colors.bottomcolor = SUPERAZUL;
		map->colors.topcolor = ROJO;
		map->colors.groundcolor = VERDE;
	}
	colorize(map);
}
