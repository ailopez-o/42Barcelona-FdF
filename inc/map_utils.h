/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:34:48 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/12 13:34:51 by aitorlope        ###   ########.fr       */
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
int		line_elems(char **elems);
void	z_limits(char **splited, t_map *map);
#endif
