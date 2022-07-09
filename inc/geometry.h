/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:26:32 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 19:26:35 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GEOMETRY_H
# define GEOMETRY_H

void	traslate(t_point *points, t_point move, int len);
void	scale(t_point *points, int scale, int len);
void	isometric(t_map *map);

#endif
