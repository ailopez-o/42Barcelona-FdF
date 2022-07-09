/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:27:06 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 19:27:08 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MATRIX_H
# define MATRIX_H

void	orto_proyection(t_point *points, t_point *proyection, int len);
void	rotate_x(t_point *points, t_point *proyection, float ang, int len);
void	rotate_y(t_point *points, t_point *proyection, float ang, int len);
void	rotate_z(t_point *points, t_point *proyection, float ang, int len);
#endif
