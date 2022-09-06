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

/* DEFINES NORMINETTE REFUSED
#define XCENTER				((WINX - MENU_WIDTH) / 2) + MENU_WIDTH
#define YCENTER				WINY / 2
*/

int		draw_map(t_meta *meta, int fit);
void	load_map(t_map *map, char *path);
void	generate_background(t_meta *meta, int backcolor, int menucolor);
void	draw_menu(t_meta *meta);
void	load_color(int max, int min, t_point *point, t_colors	colors);
void	generate_stars(t_meta *meta);
#endif
