/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:27:13 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 19:27:16 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UTILS_H
# define UTILS_H

void	dbl_free(char **ptr);
int		ft_round(double num);
void	matrix_init(float (*matrix)[3]);
void	print_nbr(t_meta *meta, int x, int y, int nbr);
void	print_str(t_meta *meta, int x, int y, char *str);
void	copy_map(t_point *src, t_point *dst, int len);
int		valid_pixel(t_point pixel);
#endif
