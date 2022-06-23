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

int	keyrelease(int keycode, t_meta *meta)
{
	printf("Keycode Press [%d]\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(meta->vars.mlx, meta->vars.win);
		exit(0);
	}
	if (keycode == 18)
		generate_background(meta, 0xFF0000);
	if (keycode == 19)
		generate_background(meta, 0x00FF00);
	if (keycode == 20)
		generate_background(meta, 0x000000);
	if (keycode == 21)
		generate_background(meta, 0xFF4534);

	if (meta->bitmap.img)
		draw_bitmap(meta, 0, 0);	
	return(0);
}
