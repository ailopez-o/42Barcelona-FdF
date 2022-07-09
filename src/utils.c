/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:04:21 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/29 16:04:25 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"

void draw_bitmap(t_meta *meta, int x0, int y0)
{
    mlx_put_image_to_window(meta->vars.mlx, meta->vars.win, meta->bitmap.img, x0, y0);
}


void dbl_free(char **ptr)
{
    int i;

    if (!ptr)
        return;
    i = 0;
    while(ptr[i])
    {
        free(ptr[i]);
        i++;
    }
    free (ptr);
}

void	terminate(void)
{
	/*
    if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	*/
    exit(1);
}

