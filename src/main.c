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
	t_meta 		meta;

	// Cargamos el mapa
	if (load_map(&meta.map) == 0)
		return (0);
	// Creo una instancia MLX
    meta.vars.mlx = mlx_init();
	// Creo una nueva ventana
    meta.vars.win = mlx_new_window(meta.vars.mlx, WINX, WINY, "FDF - ailopez-");
	// Creo una imagen
  	meta.bitmap.img = mlx_new_image(meta.vars.mlx, WINX, WINY);
	// Creo un buffer bitmap	
    meta.bitmap.buffer = mlx_get_data_addr(meta.bitmap.img , \
		&meta.bitmap.bitxpixel, &meta.bitmap.lines, &meta.bitmap.endian);
 	
	//mlx_string_put(meta.vars.mlx, meta.vars.win, 10, 10, 0x321109, "Hello World");
	
	// Capturamos eventos
	mlx_hook(meta.vars.win, 2, 0, key_press, &meta);
	//mlx_hook(meta.vars.win, 17, 0, close, &meta);
	mlx_hook(meta.vars.win, 4, 0, mouse_press, &meta);
	mlx_hook(meta.vars.win, 5, 0, mouse_release, &meta);
	mlx_hook(meta.vars.win, 6, 0, mouse_move, &meta);	
	

	// Loop esperando eventos
    mlx_loop(meta.vars.mlx);
	free (meta.map.points);
	free (meta.map.proyect3D);
	free (meta.map.proyect2D);	
	return(0);
}
