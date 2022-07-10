/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:36:55 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/29 16:01:37 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/miniliblx/minilibx_macos/mlx.h"
#include "../inc/map.h"
#include "../inc/control_keys.h"
#include "../inc/control_mouse.h"
#include "../inc/control_utils.h"
#include "../inc/errors.h"
#include <stdlib.h>

int main(int argv, char **argc)
{
	t_meta 		meta;

	if(argv != 2)
		terminate(ERR_ARGS);
	if (load_map(&meta.map, argc[1]) < 0)
		terminate(ERR_MAP);
    meta.vars.mlx = mlx_init();
    meta.vars.win = mlx_new_window(meta.vars.mlx, WINX, WINY, "FDF - ailopez-");
  	meta.bitmap.img = mlx_new_image(meta.vars.mlx, WINX, WINY);
    meta.bitmap.buffer = mlx_get_data_addr(meta.bitmap.img , \
		&meta.bitmap.bitxpixel, &meta.bitmap.lines, &meta.bitmap.endian);
	if (draw_map(&meta, FIT) < 0)
		terminate(ERR_MAP);	
	mlx_hook(meta.vars.win, 2, 0, key_press, &meta);
	mlx_hook(meta.vars.win, 3, 0, key_release, &meta);
	mlx_hook(meta.vars.win, 4, 0, mouse_press, &meta);
	mlx_hook(meta.vars.win, 5, 0, mouse_release, &meta);
	mlx_hook(meta.vars.win, 6, 0, mouse_move, &meta);	
	mlx_hook(meta.vars.win, 17, 0, terminate_program, &meta);
    mlx_loop(meta.vars.mlx);
	free (meta.map.points);	
	return(0);
}
