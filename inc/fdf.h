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
# include "keycodes.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WINX 800
# define WINY 600

# define x 0
# define y 1
# define z 2

# define ROJO 				0xc1272d
# define VERDE				0x33cc55
# define FUCSIA 			0xff255c
# define TEXT_COLOR			0xEAEAEA
# define BACKGROUND			0x222222
# define MENU_BACKGROUND	0x1E1E1E

# define COLOR_DISCO		0x9A1F6A
# define COLOR_BRICK_RED	0xC2294E
# define COLOR_FLAMINGO		0xEC4B27
# define COLOR_JAFFA		0xEF8633
# define COLOR_SAFFRON		0xF3AF3D

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

typedef struct	s_point {
	float		axis[3];
	int 		color;
}				t_point;

typedef struct	m_map {
	t_point		*points;
	t_point		*proyect3D;
	t_point		*proyect2D;
	t_point		limits;
	float		ang[3];
	float 		scale;
	int			len;
}				t_map;

typedef struct	s_meta {
	t_vars		vars;
	t_bitmap	bitmap;
	t_map		map;
	int			renders;
}				t_meta;



typedef struct	s_dot {
	int			rad;
	int			color;
	t_point 	pos;
}				t_dot;


int		keyrelease(int keycode, t_meta *meta);
int 	draw_line(t_meta *meta, t_point start, t_point end);
void 	generate_background(t_meta *meta, int color);
void 	draw_bitmap(t_meta *meta, int x0, int y0);
int		mouse_hook(int value, t_meta *meta);
int 	my_putpixel(t_meta *meta, t_point pixel);
void	draw_dot(t_meta *meta, t_point point, int radius);
void	orto_proyection(t_point *points, t_point *proyection, int len);
void	rotate_x(t_point *points, t_point *proyection, float ang, int len);
void	rotate_y(t_point *points, t_point *proyection, float ang, int len);
void	rotate_z(t_point *points, t_point *proyection, float ang, int len);
void	my_cube(t_meta *meta);
void	traslate(t_point *points, t_point move, int len);
void 	scale(t_point *points, int scale, int len);
void 	isometric(t_point *points, t_point *proyection, int len);
void	center(t_point *points, int len);
int		load_map(t_map *map);
void 	draw_map(t_meta *meta);
#endif
