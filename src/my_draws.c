/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_draws.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:41:26 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/22 13:51:34 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"


void line_elem(char **line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	printf("Line elem[%D]\n",i);
}

void load_cube(t_point *cube)
{

	for (int i = 0; i<8; i++)
		cube[i].color= FUCSIA;

	cube[0].axis[x] = -10;
	cube[0].axis[y] = -10;
	cube[0].axis[z] = -10;

	cube[1].axis[x] = 10;
	cube[1].axis[y] = -10;
	cube[1].axis[z] = -10;

	cube[2].axis[x] = 10;
	cube[2].axis[y] = 10;
	cube[2].axis[z] = -10;

	cube[3].axis[x] = -10;
	cube[3].axis[y] = 10;
	cube[3].axis[z] = -10;

	cube[4].axis[x] = -10;
	cube[4].axis[y] = -10;
	cube[4].axis[z] = 10;	

	cube[5].axis[x] = 10;
	cube[5].axis[y] = -10;
	cube[5].axis[z] = 10;

	cube[6].axis[x] = 10;
	cube[6].axis[y] = 10;
	cube[6].axis[z] = 10;

	cube[7].axis[x] = -10;
	cube[7].axis[y] = 10;
	cube[7].axis[z] = 10;	
}

void	my_cube(t_meta *meta)
{
	int			i;
	t_point		cube[8];
	t_point		proyection2D[8];
	t_point		rotated3D[8];
	static 		float	ang;
	
	load_cube(cube);
	ang += 10;
	rotate_x(cube, rotated3D, ang, 8);
	rotate_y(rotated3D, rotated3D, ang, 8);
	//rotate_z(rotated3D, rotated3D, ang, 8);
	//isometric(cube,rotated3D, 8);
	orto_proyection (rotated3D, proyection2D, 8);
	scale (proyection2D, 7, 8);
	//move.axis[x] = 300;
	//move.axis[y] = 300;
	//traslate(proyection2D, move, 8);
	center(proyection2D,8);
	generate_background(meta, 0x000000, 0x000000);
	i = 0;
	while (i < 8)
	{
		proyection2D[i].color = VERDE;
		draw_dot(meta, proyection2D[i], 1);
		printf ("[%d] - Cube[%f, %f, %f] - 3Drot[%f, %f, %f] - 2D[%f, %f, %f] - %x\n", i, cube[i].axis[x], cube[i].axis[y], cube[i].axis[z], rotated3D[i].axis[x], rotated3D[i].axis[y], rotated3D[i].axis[z], proyection2D[i].axis[x], proyection2D[i].axis[y], proyection2D[i].axis[z], proyection2D->color);
		i++;
	}
	draw_line(meta, proyection2D[0], proyection2D[1]);
	draw_line(meta, proyection2D[1], proyection2D[2]);
	draw_line(meta, proyection2D[2], proyection2D[3]);
	draw_line(meta, proyection2D[3], proyection2D[0]);

	draw_line(meta, proyection2D[4], proyection2D[5]);
	draw_line(meta, proyection2D[5], proyection2D[6]);	
	draw_line(meta, proyection2D[6], proyection2D[7]);
	draw_line(meta, proyection2D[7], proyection2D[4]);

	draw_line(meta, proyection2D[0], proyection2D[4]);
	draw_line(meta, proyection2D[1], proyection2D[5]);
	draw_line(meta, proyection2D[2], proyection2D[6]);
	draw_line(meta, proyection2D[3], proyection2D[7]);
}