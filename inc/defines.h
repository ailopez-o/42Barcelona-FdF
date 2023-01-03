/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:16:23 by aitoraudi         #+#    #+#             */
/*   Updated: 2023/01/03 10:17:03 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>

# define WINX 1920	
# define WINY 1080

# define X 0
# define Y 1
# define Z 2

# define LAT 0
# define LONG 1

# define ROJO 		0xc1272d
# define VERDE		0x33cc55
# define FUCSIA 	0xff255c
# define AZUL		0x1B8EFA
# define SUPERAZUL	0x0000FF
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
# define TEXT_COLOR			0xEAEAEA	
# define NUMBER_COLOR		0xF3AF3D

# define MENU_WIDTH			350
# define FIT_MARGIN			50

# define FIT				1
# define FREE				0

typedef struct s_point {
	float	axis[3];
	int		color;
	int		hex_color;
	bool	paint;
	float	polar[2];
}	t_point;

typedef struct m_colors {
	int	topcolor;
	int	groundcolor;
	int	bottomcolor;
	int	backcolor;
	int	menucolor;	
}	t_colors;

typedef struct s_bitmap {
	void	*img;
	char	*buffer;
	int		bitxpixel;
	int		lines;
	int		endian;
}	t_bitmap;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_keys {
	bool	b_mouse_l;
	bool	b_mouse_r;
	bool	b_keyctrl;
	t_point	last_click_l;
	t_point	last_click_r;
}	t_keys;

typedef struct m_map {
	t_point		*points;
	t_point		limits;
	t_point		source;
	t_colors	colors;
	char		*memory;
	char		**lines;
	int			zmin;
	float		ang[3];
	float		zdivisor;
	float		scale;
	int			len;
	float		brange;
	int			renders;
	bool		b_lines;
	bool		b_dots;
	bool		b_pluslines;
	bool		b_geo;
	bool		b_stars;
	bool		b_shadow;
	double		performance;
	float		proportion;
	float		radius;
}	t_map;

typedef struct s_meta {
	t_vars		vars;
	t_bitmap	bitmap;
	t_map		map;
	t_keys		keys;
}	t_meta;

# define DEF_COLOR	"\033[0;39m"
# define SH_GRAY	"\033[0;90m"
# define SH_RED		"\033[0;91m"
# define SH_GREEN	"\033[0;92m"
# define SH_YELLOW	"\033[0;93m"
# define SH_BLUE	"\033[0;94m"
# define SH_MAGENTA	"\033[0;95m"
# define SH_CYAN	"\033[0;96m"
# define SH_WHITE	"\033[0;97m"
# define SH_KNR		"\x1B[0m"
# define SH_KRED	"\x1B[31m"
# define SH_KGRN	"\x1B[32m"
# define SH_KYEL	"\x1B[33m"
# define SH_KBLU	"\x1B[34m"
# define SH_KMAG	"\x1B[35m"
# define SH_KCYN	"\x1B[36m"
# define SH_KWHT	"\x1B[37m"
# define U_ORANGE	"\033[48:5:208m"
# define U_WHITE	"\033[37;7:208m"
# define U_YELLOW	"\033[33;7:208m"
# define U_BLUE		"\033[34;7:208m"

#endif
