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
#include "mlx/mlx.h"
#include <math.h>
#include <unistd.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0	
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
    	mlx_pixel_put(mlx, win, pixelX, pixelY, color);
    	pixelX += deltaX;
    	pixelY += deltaY;
    	--pixels;
	}
	return(1);
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 1920, 1080, "Tutorial Window - Draw Line");
	int startx;
	int starty;
	int color;

	int color_start = 0x007788;


	for (int i = 0; i < 100; i++)
	{

		color = color_start;
		startx = 1920;
		starty = 1080;
		while (startx > 0)
		{
			draw_line(mlx, win, startx, starty, 0, 0, color);
			startx = startx - 100;
			color -= 100;
		}

		color = color_start;
		startx = 0;
		starty = 1080;

		while (startx < 1920)
		{
			draw_line(mlx, win, startx, starty, 1920, 0, color);
			startx = startx + 100;
			color -= 100;
		}

		color_start = color_start + 0x010000;

	usleep(100);
	}

    mlx_loop(mlx);
	return(0);
}
