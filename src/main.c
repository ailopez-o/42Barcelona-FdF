/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:36:55 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/21 14:36:59 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"



int main()
{
	t_vars	vars;
	int startx;
	int starty;
	int color;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WINX, WINY, "Tutorial Window - Draw Line");
	mlx_hook(vars.win, 2, 1L<<0, keyrelease, &vars);
    mlx_loop(vars.mlx);
	return(0);
}
