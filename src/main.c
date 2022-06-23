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
	t_meta meta;

	// Creo una instancia MLX
    meta.vars.mlx = mlx_init();
	// Creo una nueva ventana
    meta.vars.win = mlx_new_window(meta.vars.mlx, WINX, WINY, "FDF - ailopez-");
	// Creo una imagen
  	meta.bitmap.img = mlx_new_image(meta.vars.mlx, WINX, WINY);
	// Creo un buffer bitmap	
    meta.bitmap.buffer = mlx_get_data_addr(meta.bitmap.img , \
		&meta.bitmap.bitxpixel, &meta.bitmap.lines, &meta.bitmap.endian);	
	// Capturamos los eventos del teclado
	mlx_hook(meta.vars.win, 2, 1L<<0, keyrelease, &meta);
	// Loop esperando eventos
    mlx_loop(meta.vars.mlx);
	return(0);
}
