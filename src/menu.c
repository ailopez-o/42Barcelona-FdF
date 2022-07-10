/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:38:45 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 12:38:50 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/miniliblx/minilibx_macos/mlx.h"
#include "../lib/libft/libft.h"
#include "../inc/map.h"
#include <stdlib.h>

#define CONTROL_BOX			340
#define DRAWINFO_BOX		40
#define MAPINFO_BOX			550
#define COLORSCHEME_BOX		800
#define LINE_SIZE			30			
#define MENU_TAB			30
#define TEXT_COLOR			0xEAEAEA

static void	draw_colorscheme(t_meta *meta)
{
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, COLORSCHEME_BOX, \
	TEXT_COLOR, "//// COLORSCHEME ////");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, COLORSCHEME_BOX + \
	LINE_SIZE * 2, TEXT_COLOR, "0: DEFAULT");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, COLORSCHEME_BOX + \
	LINE_SIZE * 3, TEXT_COLOR, "1: TERRAIN");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, COLORSCHEME_BOX + \
	LINE_SIZE * 4, TEXT_COLOR, "2: BLACK & WHITE");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, COLORSCHEME_BOX + \
	LINE_SIZE * 5, TEXT_COLOR, "3: WHITE & BLACK");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, COLORSCHEME_BOX + \
	LINE_SIZE * 6, TEXT_COLOR, "4: DISCO");
}

static void	draw_mapinfo(t_meta *meta)
{
	char	*str;
	char	*stritoa;

	str = ft_calloc(10, 1);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX, \
	TEXT_COLOR, "//// MAP INFO ////");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + \
	LINE_SIZE * 2, TEXT_COLOR, "Size:");
	stritoa = ft_itoa(meta->map.len);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, MAPINFO_BOX + \
	LINE_SIZE * 2, TEXT_COLOR, stritoa);
	free (stritoa);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + \
	LINE_SIZE * 3, TEXT_COLOR, "Xmax:");
	gcvt(meta->map.limits.axis[X], 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, MAPINFO_BOX + \
	LINE_SIZE * 3, TEXT_COLOR, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + \
	LINE_SIZE * 4, TEXT_COLOR, "Ymax:");
	gcvt(meta->map.limits.axis[Y], 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, MAPINFO_BOX + \
	LINE_SIZE * 4, TEXT_COLOR, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + \
	LINE_SIZE * 5, TEXT_COLOR, "Zmax:");
	gcvt(meta->map.limits.axis[Z], 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, MAPINFO_BOX + \
	LINE_SIZE * 5, TEXT_COLOR, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + \
	LINE_SIZE * 6, TEXT_COLOR, "Zmin:");
	gcvt(meta->map.zmin, 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 78, MAPINFO_BOX + \
	LINE_SIZE * 6, TEXT_COLOR, str);
	free(str);
}

static void	draw_controls(t_meta *meta)
{
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX, \
	TEXT_COLOR, "//// CONTROLS ////");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + \
	LINE_SIZE * 2, TEXT_COLOR, "Scroll: Zom In/Out");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + \
	LINE_SIZE * 3, TEXT_COLOR, "Left Click: Rotate X/Y axis");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + \
	LINE_SIZE * 4, TEXT_COLOR, "Arrows: Rotate X/Y axis");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + \
	LINE_SIZE * 5, TEXT_COLOR, "Q/W: Rotate Z axis");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + \
	LINE_SIZE * 6, TEXT_COLOR, "Right Click: Move");
}

static void	draw_info(t_meta *meta)
{
	char	*str;

	str = ft_calloc(10, 1);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, DRAWINFO_BOX, \
	TEXT_COLOR, "//// DRAW INFO ////");
	gcvt(meta->map.renders, 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, \
	DRAWINFO_BOX + LINE_SIZE * 2, TEXT_COLOR, "Reenders:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 120, \
	DRAWINFO_BOX + LINE_SIZE * 2, TEXT_COLOR, str);
	gcvt(meta->map.ang[X], 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, \
	DRAWINFO_BOX + LINE_SIZE * 3, TEXT_COLOR, "X Axis:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 120, \
	DRAWINFO_BOX + LINE_SIZE * 3, TEXT_COLOR, str);
	gcvt(meta->map.ang[Y], 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, \
	DRAWINFO_BOX + LINE_SIZE * 4, TEXT_COLOR, "Y Axix:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 120, \
	DRAWINFO_BOX + LINE_SIZE * 4, TEXT_COLOR, str);
	gcvt(meta->map.ang[Z], 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, \
	DRAWINFO_BOX + LINE_SIZE * 5, TEXT_COLOR, "Z Axix:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 120, \
	DRAWINFO_BOX + LINE_SIZE * 5, TEXT_COLOR, str);
	gcvt(meta->map.scale, 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, \
	DRAWINFO_BOX + LINE_SIZE * 6, TEXT_COLOR, "Zoom:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 120, \
	DRAWINFO_BOX + LINE_SIZE * 6, TEXT_COLOR, str);
	gcvt(meta->map.zdivisor, 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, \
	DRAWINFO_BOX + LINE_SIZE * 7, TEXT_COLOR, "Z Divisor:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 120, \
	DRAWINFO_BOX + LINE_SIZE * 7, TEXT_COLOR, str);
	gcvt(meta->map.brange, 5, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, \
	DRAWINFO_BOX + LINE_SIZE * 8, TEXT_COLOR, "Blending:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 120, \
	DRAWINFO_BOX + LINE_SIZE * 8, TEXT_COLOR, str);	
	free(str);
}

void	draw_menu(t_meta *meta)
{
	draw_controls(meta);
	draw_info(meta);
	draw_mapinfo(meta);
	draw_colorscheme(meta);
}
