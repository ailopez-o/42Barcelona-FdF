/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:26:13 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/09 13:26:21 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/get_next_line.h"
#include "../lib/libft/libft.h"
#include "../inc/defines.h"
#include "../inc/utils.h"
#include "../inc/draw_utils.h"
#include "../inc/map_utils.h"
#include "../inc/errors.h"
#include <fcntl.h>

/*
*	Acording the z value of the point and de max and min values of the map
*	this function set the color needed of the point received.
*	All the colors are defined in fdf.h 
*/

void	load_color(int max, int min, t_point *point, t_colors	colors)
{
	point->color = DEFAULT_COLOR;
	if (point->axis[Z] == max)
		point->color = colors.topcolor;
	else if (point->axis[Z] == 0)
		point->color = colors.groundcolor;
	else if (point->axis[Z] == min && min != 0)
		point->color = colors.bottomcolor;
	else if (point->axis[Z] > 0)
		point->color = gradient(colors.groundcolor, colors.topcolor, \
		max, point->axis[Z]);
	else
		point->color = gradient(colors.bottomcolor, colors.groundcolor, \
		-min, - (min - point->axis[Z]));
}

void	load_hexcolors(t_map *map, char *line)
{
	char	**color;

	if (ft_strchr(line, ',') != 0)
	{
		color = ft_split(line, ',');
		map->points[map->len].color = strtol(color[1] + 2, NULL, 16);
		dbl_free(color);
	}
}

/* 
*	Splits the info of line to storage
*	the points in the map->point array. 
*	Using map->len as index of the array
*/

static void	load_points(char *line, t_map *map, int numline)
{
	char	**splited;
	int		i;

	write(1, "⚡", 4);
	splited = ft_split(line, ' ');
	i = 0;
	while (splited[i] && splited[i][0] != '\n')
	{
		if (!valid_point(&splited[i][0]))
			terminate(ERR_EMPTY);
		map->points[map->len].axis[Z] = ft_atoi(&splited[i][0]);
		map->points[map->len].axis[X] = i - map->limits.axis[X] / 2;
		map->points[map->len].axis[Y] = numline - map->limits.axis[Y] / 2;
		load_color((int)map->limits.axis[Z], map->zmin, \
		&map->points[map->len], map->colors);
		load_hexcolors(map, splited[i]);
		i++;
		map->len++;
	}
	dbl_free(splited);
}

/* 
*	This function determinates the max values x, y, z of the map
*	and return -1 if the maps has different line sizes.
*/

static void	map_size(char *path, t_map *map)
{
	char	*line;
	char	**splited;
	int		linelen;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 2)
		terminate(ERR_OPEN);
	line = get_next_line(fd);
	while (line != NULL)
	{
		splited = ft_split(line, ' ');
		z_limits(splited, map);
		linelen = line_elems(splited);
		if (map->limits.axis[X] == 0)
			map->limits.axis[X] = linelen;
		if (map->limits.axis[X] != linelen)
			terminate(ERR_LINE);
		map->len += map->limits.axis[X];
		map->limits.axis[Y]++;
		dbl_free(splited);
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
}

int	load_map(t_map *map, char *path)
{
	int		fd;
	char	*line;
	int		numline;

	map_ini(map, 1);
	map_size(path, map);
	map->points = ft_calloc (map->len, sizeof(t_point));
	if (map->points == NULL)
		terminate(ERR_MEM);
	fd = open(path, O_RDONLY);
	if (fd < 2)
		terminate(ERR_OPEN);
	numline = 0;
	map->len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		numline++;
		load_points(line, map, numline);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}
