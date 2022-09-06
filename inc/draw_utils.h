/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:28:01 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 19:28:03 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

int		draw_line(t_meta *meta, t_point start, t_point end);
void	draw_dot(t_meta *meta, t_point point, int radius);
int		gradient(int startcolor, int endcolor, int len, int pix);
int		my_putpixel(t_meta *meta, t_point pixel);
void	shadow(t_point *points, int len);
#endif
