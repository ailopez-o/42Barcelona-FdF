/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:51:19 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/22 13:51:24 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"

int	keyrelease(int keycode, t_vars *vars)
{
	printf("Keycode Press [%d]\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == 18)
		draw_line_fast(vars,0,0,0,0, 0xFF0000);
	if (keycode == 19)
		draw_line(vars, 20, 40, 1920, 1080, 0x00FF00);
	if (keycode == 20)
		draw_line(vars, 500, 800, 1920, 1080, 0x0000FF);
	if (keycode == 21)
		draw_line(vars, 0, 0, 1920, 1080, 0xFF0000);
	return(0);
}
