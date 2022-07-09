/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:26:51 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 19:26:54 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAP_H
# define MAP_H

# include <stdbool.h>

# define WINX 1920	
# define WINY 1080

# define x 0
# define y 1
# define z 2

# define ROJO 		0xc1272d
# define VERDE		0x33cc55
# define FUCSIA 	0xff255c
# define AZUL		0x1B8EFA
# define CARBON		0x151515
# define WHITE		0xBBBBBB
# define DISCO		0x9A1F6A
# define BRICK_RED	0xC2294E
# define FLAMINGO	0xEC4B27
# define JAFFA		0xEF8633
# define SAFFRON	0xF3AF3D

# define DEFAULT_COLOR		JAFFA
# define BOTTOM_COLOR		AZUL
# define TOP_COLOR			BRICK_RED
# define GROUND_COLOR		SAFFRON
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

typedef struct	s_keys {
	bool		b_mouseL;
	bool		b_mouseR;
	bool		b_keyctrl;
	t_point		last_clickL;
	t_point		last_clickR;
}			t_keys;

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

typedef struct	s_meta {
	t_vars		vars;
	t_bitmap	bitmap;
	t_map		map;
	t_keys		keys;
}				t_meta;

int		draw_map(t_meta *meta, int fit);
int		load_map(t_map *map, char *path);
void	colorize(t_map *map);
void	map_ini(t_map *map);
void	z_division(t_point *proyect, float divisor, int len);
void	copy_map(t_point *src, t_point *dst, int len);
void	generate_background(t_meta *meta, int backcolor, int menucolor);
void	wired(t_meta *meta, t_point *wire);
void	doted(t_meta *meta, t_point *proyect);
void	draw_menu(t_meta *meta);
void	load_color(int max, int min, t_point *point, t_colors	colors);
#endif
