/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:51:50 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/22 13:51:55 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

# include "../miniliblx/minilibx_macos/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define WINX 800
# define WINY 600

# define R(a) (a) >> 16
# define G(a) ((a) >> 8) & 0xFF
# define B(a) (a) & 0xFF
# define RGB(a, b, c) ((a) << 16) + ((b) << 8) + (c)

typedef struct	s_bitmap {
	void	*img;
	char	*buffer;
	int		bitxpixel;
	int		lines;
	int		endian;
}				t_bitmap;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_meta {
	t_vars		vars;
	t_bitmap	bitmap;
}				t_meta;


int		keyrelease(int keycode, t_meta *meta);
int 	draw_line(t_vars *vars, int beginX, int beginY, int endX, int endY, int color);
void 	generate_background(t_meta *meta, int color);
int 	draw_bitmap(t_meta *meta, int x0, int y0);
#endif
