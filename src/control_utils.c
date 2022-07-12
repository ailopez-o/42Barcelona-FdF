/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:45:09 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/10 19:45:12 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/miniliblx/minilibx_macos/mlx.h"
#include "../lib/libft/libft.h"
#include "../inc/defines.h"
#include "../inc/keycodes.h"
#include "../inc/map.h"
#include <stdlib.h>
#include <errno.h>

void	angle(float *ang, float value)
{
	*ang += value;
	if (*ang < 0)
			*ang = 360 + *ang;
	if (*ang >= 360)
			*ang = *ang - 360;
}

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

int	terminate_program(void *param)
{
	t_meta	*meta;

	meta = (t_meta *)param;
	mlx_destroy_window(meta->vars.mlx, meta->vars.win);
	free(meta->map.points);
	exit(0);
}

void	terminate(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}
