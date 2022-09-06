/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 19:26:10 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 19:26:14 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CONTROL_UTILS_H
# define CONTROL_UTILS_H

void	angle_control(int key, t_meta *meta);
void	angle(float *ang, float value);
void	colorize(t_map *map);
int		terminate_program(void *param);
void	terminate(char *s);
void	control_colorscheme(int key, t_map *map);
#endif
