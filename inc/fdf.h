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

# include "../lib/miniliblx/minilibx_macos/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WINX 800
# define WINY 600


# define ROJO 0xc1272d
# define VERDE 0x33cc55
# define FUCSIA 0xff255c



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
	int		winX;
	int		winY;
}				t_vars;

typedef struct	s_meta {
	t_vars		vars;
	t_bitmap	bitmap;
}				t_meta;

typedef struct	s_coord {
	int		X;
	int 	Y;
	int 	color;
}				t_coord;

typedef struct	s_pcoord {
	double		X;
	double 		Y;
	int 		color;
}				t_pcoord;

typedef struct	s_line {
	t_coord		start;
	t_coord 	end;
}				t_line;

typedef struct	s_dot {
	int			rad;
	int			color;
	t_coord 	pos;
}				t_dot;

int		keyrelease(int keycode, t_meta *meta);
int 	draw_line(t_meta *meta, t_line line);
void 	generate_background(t_meta *meta, int color);
void 	draw_bitmap(t_meta *meta, int x0, int y0);
int		mouse_hook(int value, t_meta *meta);
int 	my_putpixel(t_meta *meta, t_coord pixel);
void 	draw_dot(t_meta *meta, t_coord pos, int radius);
#endif
