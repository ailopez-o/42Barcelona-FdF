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
# include "../lib/libft/libft.h"
# include "../inc/get_next_line.h"
# include "keycodes.h"
# include <stdbool.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

# define WINX 1920	
# define WINY 1080

# define x 0
# define y 1
# define z 2

# define ON_KEYDOWN		2
# define ON_KEYUP		3
# define ON_MOUSEDOWN	4
# define ON_MOUSEUP		5
# define ON_MOUSEMOVE	6
# define ON_EXPOSE		12
# define ON_DESTROY		17

# define ROJO 				0xc1272d
# define VERDE				0x33cc55
# define FUCSIA 			0xff255c
# define AZUL				0x1B8EFA
# define CARBON				0x151515
# define WHITE				0xBBBBBB
# define COLOR_DISCO		0x9A1F6A
# define COLOR_BRICK_RED	0xC2294E
# define COLOR_FLAMINGO		0xEC4B27
# define COLOR_JAFFA		0xEF8633
# define COLOR_SAFFRON		0xF3AF3D

# define DEFAULT_COLOR		COLOR_JAFFA
# define BOTTOM_COLOR		AZUL
# define TOP_COLOR			COLOR_BRICK_RED
# define GROUND_COLOR		COLOR_SAFFRON
# define TEXT_COLOR			0xEAEAEA
# define BACK_COLOR			0x151515
# define MENU_COLOR			0x202020

# define MENU_WIDTH			350



# define LIMIT_MINX			MENU_WIDTH + FIT_MARGIN
# define LIMIT_MAXX			WINX - FIT_MARGIN
# define LIMIT_MINY			FIT_MARGIN
# define LIMIT_MAXY			WINY - FIT_MARGIN


#define XCENTER				(((WINX - MENU_WIDTH) / 2) + MENU_WIDTH);
#define YCENTER				WINY/2;

# define FIT_MARGIN			50
# define FIT				1
# define FREE				0

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

typedef struct	m_colors {
	int			topcolor;
	int			groundcolor;
	int			bottomcolor;
	int			backcolor;
	int 		menucolor;	
}	t_colors;

typedef struct	m_map {
	t_point		*points;
	t_point		limits;
	t_point		source;	
	t_colors	colors;	
	int			zmin;
	float		ang[3];
	float		zdivisor;
	float 		scale;
	int			len;
	int			renders;
	bool		b_lines;
	bool		b_dots;
}				t_map;


typedef struct	s_keys {
	bool		b_mouseL;
	bool		b_mouseR;
	bool		b_keyctrl;
	t_point		last_clickL;
	t_point		last_clickR;
}			t_keys;



typedef struct	s_meta {
	t_vars		vars;
	t_bitmap	bitmap;
	t_map		map;
	t_keys		keys;
}				t_meta;



typedef struct	s_dot {
	int			rad;
	int			color;
	t_point 	pos;
}				t_dot;


int		key_press(int key, void *param);
int		key_release(int key, void *param);
int		mouse_move(int X, int Y, void *param);
int		mouse_release(int button, int X, int Y, void *param);
int		mouse_press(int button, int X, int Y, void *param);
int 	draw_line(t_meta *meta, t_point start, t_point end);
void 	generate_background(t_meta *meta, int backcolor, int menucolor);
void 	draw_bitmap(t_meta *meta, int x0, int y0);
int 	my_putpixel(t_meta *meta, t_point pixel);
t_point set_point(float X, float Y, float Z, int color);
void	draw_dot(t_meta *meta, t_point point, int radius);
void	orto_proyection(t_point *points, t_point *proyection, int len);
void	rotate_x(t_point *points, t_point *proyection, float ang, int len);
void	rotate_y(t_point *points, t_point *proyection, float ang, int len);
void	rotate_z(t_point *points, t_point *proyection, float ang, int len);
void	my_cube(t_meta *meta);
void	traslate(t_point *points, t_point move, int len);
void 	scale(t_point *points, int scale, int len);
void 	isometric(t_map *map);
int 	load_map(t_map *map, char *path);
int 	draw_map(t_meta *meta, int fit);
int		gradient(int startcolor, int endcolor, int len, int pix);
void	terminate(void);
int		fit(t_map *map);
void 	dbl_free(char **ptr);
void	copy_map(t_point *src, t_point *dst, int len);
void	z_division(t_point *proyect, float divisor, int len);
void	draw_menu(t_meta *meta);
void	wired(t_meta *meta, t_point *wire);
void	doted(t_meta *meta, t_point *proyect);
void	copy_map(t_point *src, t_point *dst, int len);
void	z_division(t_point *proyect, float divisor, int len);
void	map_ini(t_map *map);
void	colorize(t_map *map);

#endif
