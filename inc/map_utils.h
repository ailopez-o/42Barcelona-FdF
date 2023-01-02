/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:34:48 by aitorlope         #+#    #+#             */
/*   Updated: 2023/01/02 16:46:00 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

void	colorize(t_map *map);
void	wired(t_meta *meta, t_point *wire);
void	doted(t_meta *meta, t_point *proyect);
void	z_division(t_point *proyect, float divisor, int len);
void	map_ini(t_map *map, int total);
void	show_info(t_map *map);
void	z_limits(char **splited, t_map *map);
int		valid_point(char *value);
int		has_hexcolors(char *line);
void	load_color(int max, int min, t_point *point, t_colors	colors);
#endif
