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


void load_cube(t_point *cube)
{

	for (int i = 0; i<8; i++)
		cube[i].color= FUCSIA;

	cube[0].axis[x] = 100;
	cube[0].axis[y] = 100;
	cube[0].axis[z] = -50;

	cube[1].axis[x] = 200;
	cube[1].axis[y] = 100;
	cube[1].axis[z] = -50;

	cube[2].axis[x] = 100;
	cube[2].axis[y] = 200;
	cube[2].axis[z] = -50;

	cube[3].axis[x] = 200;
	cube[3].axis[y] = 200;
	cube[3].axis[z] = -50;

	cube[4].axis[x] = 100;
	cube[4].axis[y] = 100;
	cube[4].axis[z] = 50;	

	cube[5].axis[x] = 200;
	cube[5].axis[y] = 100;
	cube[5].axis[z] = 50;

	cube[6].axis[x] = 100;
	cube[6].axis[y] = 200;
	cube[6].axis[z] = 50;

	cube[7].axis[x] = 100;
	cube[7].axis[y] = 100;
	cube[7].axis[z] = 50;	
}

int main()
{
	t_meta 		meta;
	int			i;
	t_point		cube[8];
	t_point		proyection2D[8];

	// Creo una instancia MLX
    meta.vars.mlx = mlx_init();
	meta.vars.winX = WINX;
	meta.vars.winY = WINY;
	// Creo una nueva ventana
    meta.vars.win = mlx_new_window(meta.vars.mlx, WINX, WINY, "FDF - ailopez-");
	// Creo una imagen
  	meta.bitmap.img = mlx_new_image(meta.vars.mlx, WINX, WINY);
	// Creo un buffer bitmap	
    meta.bitmap.buffer = mlx_get_data_addr(meta.bitmap.img , \
		&meta.bitmap.bitxpixel, &meta.bitmap.lines, &meta.bitmap.endian);	

	load_cube(cube);
	orto_proyection (cube, proyection2D, 8);
	i = 0;
	while (i < 8)
	{
		draw_dot(&meta, proyection2D[i], 1);
		printf ("[%f, %f, %f] - [%f, %f, %f]\n", cube[i].axis[x], cube[i].axis[y], cube[i].axis[z], proyection2D[i].axis[x], proyection2D[i].axis[y], proyection2D[i].axis[z]);
		i++;
	}



	draw_bitmap(&meta, 0, 0);

	// Capturamos los eventos del teclado
	mlx_hook(meta.vars.win, 2, 1L<<0, keyrelease, &meta);
	// Capturamos eventos del ratóm
	mlx_mouse_hook(meta.vars.win, mouse_hook, &meta);
	// Loop esperando eventos
    mlx_loop(meta.vars.mlx);
	return(0);
}
