/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:34:10 by aitorlope         #+#    #+#             */
/*   Updated: 2023/01/01 17:21:05 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../lib/libft/libft.h"
#include "../inc/utils.h"

int	line_elems(char **elems)
{
	int		i;

	i = 0;
	while (elems[i] && elems[i][0] != '\n')
		i++;
	return (i);
}

void	z_limits(char **splited, t_map *map)
{
	int	i;
	int	valor;

	write(1, "🧱", 4);
	i = 0;
	while (splited[i])
	{
		valor = ft_atoi(&splited[i][0]);
		if (map->limits.axis[Z] < valor)
			map->limits.axis[Z] = valor;
		if (map->zmin > valor)
			map->zmin = valor;
		i++;
	}
}

int	valid_point(char *value)
{
	int	valid;

	valid = 0;
	if (*value == '-' || *value == '+' || ft_isdigit(*value))
		valid++;
	value++;
	while (ft_isdigit(*value))
	{
		value++;
		valid++;
	}
	if (valid == 0)
		return (0);
	else
		return (1);
}

static void	map_ini_colors(t_map *map)
{
	map->colors.backcolor = BACK_COLOR;
	map->colors.menucolor = MENU_COLOR;
	map->colors.bottomcolor = BOTTOM_COLOR;
	map->colors.groundcolor = GROUND_COLOR;
	map->colors.topcolor = TOP_COLOR;
}

void	map_ini(t_map *map, int total)
{
	if (total)
	{
		map->len = 0;
		map->limits.axis[X] = 0;
		map->limits.axis[Y] = 0;
		map->limits.axis[Z] = 0;
		map->zmin = 0;
	}
	map->b_lines = 1;
	map->b_dots = 0;
	map->b_pluslines = 0;
	map->b_geo = 0;
	map->b_stars = 0;
	map->b_shadow = 1;
	map->scale = 1;
	map->zdivisor = 1;
	map->brange = 0;
	map->source.axis[X] = ((WINX - MENU_WIDTH) / 2) + MENU_WIDTH;
	map->source.axis[Y] = WINY / 2;
	map->source.axis[Z] = 0;
	map->ang[X] = 0;
	map->ang[Y] = 0;
	map->ang[Z] = 0;
	map_ini_colors(map);
}
