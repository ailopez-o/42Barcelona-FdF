/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:01:53 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/29 16:01:57 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/fdf.h"

void	show_info(t_map *map)
{
	printf("\nMapa Leido [%d][%d][%d][%d] - SIZE[%d] \n", (int)map->limits.axis[x], (int)map->limits.axis[y], (int)map->limits.axis[z], map->zmin, map->len);
}

/* 
*	Acording the z value of the point and de max and min values of the map
*	this function set the color needed of the point received.
*	All the colors are defined in fdf.h 
*/

void	load_color(int max, int min, t_point *point, t_colors	colors)
{
	point->color = DEFAULT_COLOR;
	if (point->axis[z] == max)
		point->color = colors.topcolor;
	else if (point->axis[z] == 0)
		point->color = colors.groundcolor;
	else if (point->axis[z] == min && min != 0)
		point->color = colors.bottomcolor;
	else if (point->axis[z] > 0)
		point->color = gradient(colors.groundcolor, colors.topcolor, max, point->axis[z]);
	else
		point->color = gradient(colors.bottomcolor, colors.groundcolor, -min, - (min - point->axis[z]));
}

/* 
*	Splits the info of line to storage
*	the points in the map->point array. 
*	Using map->len as index of the array
*/

void	load_points(char *line, t_map *map, int numline)
{
	char	**splited;
	char	**color;
	int		i;

	write(1, ".", 1);
	splited = ft_split(line, ' ');
	i = 0;
	while (splited[i])
	{
		map->points[map->len].axis[z] = ft_atoi(&splited[i][0]);
		map->points[map->len].axis[x] = i - map->limits.axis[x] / 2;
		map->points[map->len].axis[y] = numline - map->limits.axis[y] / 2;
		load_color((int)map->limits.axis[z], map->zmin, &map->points[map->len], map->colors);
		if (ft_strchr(splited[i], ',') != 0)
		{
			color = ft_split(splited[i], ',');
			map->points[map->len].color = strtol(color[1] + 2, NULL, 16);
			dbl_free(color);
		}
		i++;
		map->len++;
	}
	dbl_free(splited);
}

int	line_size(char *line)
{
	int		i;
	char	**split;

	split = ft_split(line, ' ');
	i = 0;
	while (split[i])
		i++;
	dbl_free(split);
	return (i);
}

void	map_size(int fd, t_map *map)
{
	char	*line;
	int		i;
	char	**splited;
	int		valor;

	map->len = 0;
	map->limits.axis[y] = 0;
	map->limits.axis[z] = 0;
	map->zmin = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		write(1, "*", 1);
		splited = ft_split(line, ' ');
		i = 0;
		while (splited[i])
		{
			valor = ft_atoi(&splited[i][0]);
			if (map->limits.axis[z] < valor)
				map->limits.axis[z] = valor;
			if (map->zmin > valor)
				map->zmin = valor;
			i++;
		}
		map->limits.axis[x] = line_size(line);
		map->len += map->limits.axis[x];
		map->limits.axis[y]++;
		dbl_free(splited);
		free(line);
		line = get_next_line(fd);
	}
}

void	map_ini(t_map *map)
{
	map->b_lines = 1;
	map->b_dots = 0;
	map->renders = 0;
	map->scale = 1;
	map->zdivisor = 1;
	map->source.axis[x] = XCENTER;
	map->source.axis[y] = YCENTER;
	map->source.axis[z] = 0;
	map->ang[x] = 0;
	map->ang[y] = 0;
	map->ang[z] = 0;
	map->colors.backcolor = BACK_COLOR;
	map->colors.menucolor = MENU_COLOR;
	map->colors.bottomcolor = BOTTOM_COLOR;
	map->colors.groundcolor = GROUND_COLOR;
	map->colors.topcolor = TOP_COLOR;
}

int	load_map(t_map *map, char *path)
{
	int		fd;
	char	*line;
	int		numline;

	map_ini(map);
	fd = open(path, O_RDONLY);
	if (fd < 2)
		return (-1);
	map_size(fd, map);
	map->points = ft_calloc (map->len, sizeof(t_point));
	close (fd);
	fd = open(path, O_RDONLY);
	if (fd < 2)
		return (-1);
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
	show_info(map);
	return (1);
}



/* 
*	This function iterate all the points of the wire array and draw a line between:
*	--> wire[i] and wire [i+1]
*	--> wire[i] and wire [i + mapsize]
*/

void	wired(t_meta *meta, t_point *wire)
{
	int	i;

	i = 0;
	while (i < meta->map.len)
	{
		if ((i + 1) % (int)meta->map.limits.axis[x] != 0)
			draw_line(meta, wire[i], wire[i + 1]);
		if ((i / (int)meta->map.limits.axis[x]) != (meta->map.limits.axis[y] - 1))
			draw_line(meta, wire[i], wire[i + (int)meta->map.limits.axis[x]]);
		i++;
	}
}

/* 
*	This function iterate all the points of the array and draw a dot for each point
*/

void	doted(t_meta *meta, t_point *proyect)
{
	int	i;

	i = 0;
	while (i < meta->map.len)
	{
		draw_dot(meta, proyect[i], 1);
		i++;
	}
}

/* 
*	This function copy len points of the array from src to dst
*/

void	copy_map(t_point *src, t_point *dst, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

/* 
*	This function iterate len points of the array and 
*	divide de z axis by divisor
*/

void	z_division(t_point *proyect, float divisor, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		proyect[i].axis[z] = proyect[i].axis[z] / divisor;
		i++;
	}
}

int	limits(t_point *points, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (points[i].axis[x] < LIMIT_MINX || \
			points[i].axis[x] > LIMIT_MAXX)
			return (1);
		if (points[i].axis[y] < LIMIT_MINY || \
			points[i].axis[y] > LIMIT_MAXY)
			return (1);
		i++;
	}
	return (0);
}

void parse_map(t_meta *meta, t_point *proyect)
{
	z_division(proyect, meta->map.zdivisor, meta->map.len);
	rotate_x(proyect, proyect, meta->map.ang[x], meta->map.len);
	rotate_y(proyect, proyect, meta->map.ang[y], meta->map.len);
	rotate_z(proyect, proyect, meta->map.ang[z], meta->map.len);
	orto_proyection (proyect, proyect, meta->map.len);
	scale (proyect, meta->map.scale, meta->map.len);
	traslate(proyect, meta->map.source, meta->map.len);
}

int	draw_map(t_meta *meta, int fit)
{
	t_point		*proyect;

	proyect = malloc (meta->map.len * sizeof(t_point));
	if (proyect == NULL)
		return (-1);
	meta->map.renders = meta->map.renders + 1;
	generate_background(meta, meta->map.colors.backcolor, meta->map.colors.menucolor);
	copy_map(meta->map.points, proyect, meta->map.len);
	parse_map(meta, proyect);
	if (fit)
	{
		meta->map.source.axis[x] = XCENTER;
		meta->map.source.axis[y] = YCENTER;
		meta->map.source.axis[z] = 0;
		meta->map.scale = 1;
		copy_map(meta->map.points, proyect, meta->map.len);
		parse_map(meta, proyect);
		while (!(limits(proyect, meta->map.len)))
		{
			meta->map.source.axis[x] = XCENTER;
			meta->map.source.axis[y] = YCENTER;
			meta->map.source.axis[z] = 0;
			copy_map(meta->map.points, proyect, meta->map.len);
			parse_map(meta, proyect);
			meta->map.scale = meta->map.scale + 0.2;
		}
	}
	if (meta->map.b_lines)
		wired(meta, proyect);
	if (meta->map.b_dots)
		doted(meta,proyect);
	draw_bitmap(meta, 0, 0);
	draw_menu(meta);
	free (proyect);
	return (1);
}
