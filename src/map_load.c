/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:26:13 by aitorlope         #+#    #+#             */
/*   Updated: 2023/01/02 15:40:21 by aitoraudica      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/ft_printf/inc/ft_printf.h"
#include "../inc/defines.h"
#include "../inc/utils.h"
#include "../inc/draw_utils.h"
#include "../inc/map_utils.h"
#include "../inc/errors.h"
#include "../inc/geometry.h"
#include <strings.h>
#include <math.h>
#include <fcntl.h>

#define	BLOCK_READ	500000

/*
*	Acording the z value of the point and de max and min values of the map
*	this function set the color needed of the point received.
*	All the colors are defined in fdf.h 
*/

void	load_color(int max, int min, t_point *point, t_colors	colors)
{
	point->paint = 1;
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

// set_z_limits(t_point *point, t_map map)
// {
// 	if (point->axis[Z] < map->limits.axis[Z])
		

	
// }

/* 
*	Splits the info of line to storage
*	the points in the map->point array. 
*	Using map->len as index of the array
*/

static int	load_points(char *line, t_map *map, int numline)
{
	char		**splited;
	int			i;
	static int	point_index = 0;


	//printf("\r%d points loaded", num_points);
	//write(1, "⚡", 4);
	splited = ft_split(line, ' ');
	i = 0;
	while (splited[i] && splited[i][0] != '\n')
	{
		if (!valid_point(&splited[i][0]))
			terminate(ERR_EMPTY);
		map->points[point_index].axis[Z] = ft_atoi(&splited[i][0]);
		map->points[point_index].axis[X] = i - map->limits.axis[X] / 2;
		map->points[point_index].axis[Y] = numline - map->limits.axis[Y] / 2;
		load_color((int)map->limits.axis[Z], map->zmin, \
		&map->points[point_index], map->colors);
		load_hexcolors(map, splited[i]);
		i++;
		point_index++;
	}
	dbl_free(splited);
	return (i);
}

static	void	fast_map_size(t_map *map)
{
	//char	**points;
	int		numline;
	int		i;
	int		num_elems;
	char	*line;
	char	*last_line;
	int		num_points;
	int 	len;	

	len = ft_strlen (map->map_in_memory);
	len++;
	len--;
	i = -1;
	num_elems = 0;
	len = ft_strlen (map->map_in_memory);
	map->limits.axis[Y] = 0;
	while (map->map_in_memory[++i])
	{
		if (map->map_in_memory[i] == '\n' && map->map_in_memory[i + 1] == '\0')
			break ;
		if (ft_isdigit(map->map_in_memory[i]) && (map->map_in_memory[i + 1] == ' ' || map->map_in_memory[i + 1] == '\n' || map->map_in_memory[i + 1] == '\0'))
				num_elems++;
		if (map->map_in_memory[i] == '\n')
		{
			map->limits.axis[Y]++;
			if (map->limits.axis[X] != 0 && (map->limits.axis[X] != num_elems))
				terminate(ERR_LINE);
			else
				map->limits.axis[X] = num_elems;
			 num_elems = 0;;	
		}
	}





	
	map->len = map->limits.axis[X] * map->limits.axis[Y];
	last_line = map->map_in_memory;
	line = NULL;
	num_points = 0;
	numline = 0;
	i = -1;
	map->points = ft_calloc (map->len, sizeof(t_point));
	while (map->map_in_memory[++i])
	{
		if (map->map_in_memory[i] == '\n' || map->map_in_memory[i] == '\0')
		{
			free (line);
			line = ft_substr(last_line, 0, &map->map_in_memory[i] - last_line);
			last_line = &map->map_in_memory[i + 1];
			num_points += load_points(line, map, ++numline);
			ft_printf("\r ▶ %d points reading...", num_points);
		}
	}
	ft_printf("\r ✅ %d points readed\n", num_points);
}

/* 
*	This function determinates the max values x, y, z of the map
*	and return -1 if the maps has different line sizes.
*/

// static void	map_size(char *path, t_map *map)
// {
// 	char	*line;
// 	char	**splited;
// 	int		linelen;
// 	int		fd;

// 	fd = open(path, O_RDONLY);
// 	if (fd < 2)
// 		terminate(ERR_OPEN);		
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		splited = ft_split(line, ' ');
// 		z_limits(splited, map);
// 		linelen = line_elems(splited);
// 		if (map->limits.axis[X] == 0)
// 			map->limits.axis[X] = linelen;
// 		if (map->limits.axis[X] != linelen)
// 			terminate(ERR_LINE);
// 		map->len += map->limits.axis[X];
// 		map->limits.axis[Y]++;
// 		dbl_free(splited);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close (fd);
// }



char	*fast_read(int fd)
{
	char	*buffer;
	char	*temp;
	int		byte_read;
	int		total_bytes;
	char	*map;

	buffer = malloc(BLOCK_READ * sizeof(char));
	if (buffer == NULL)
		terminate(ERR_MEM);
	map = ft_strdup("");
	total_bytes = 0;
	byte_read = BLOCK_READ;
	ft_printf("\n Map loading...\n\n");
	while (byte_read == BLOCK_READ)
	{	
		ft_bzero (buffer, BLOCK_READ);
		byte_read = read(fd, buffer, BLOCK_READ);
		temp = map;
		map = ft_strjoin(map, buffer);
		total_bytes += byte_read;
		ft_printf("\r %d kb reading", total_bytes/1024);
		free(temp);
	}
	printf("\r ✅ %d kb readed \n", total_bytes/1024);
	free(buffer);	
	close(fd);
	return (map);
}


/* 
*	Inicialize the structure
*	Get the map_size
*	Check if the map is valid
*	Read the map
*	Load each point to the structure
*/

void	load_map(t_map *map, char *path)
{
	int		fd;
	//int		numline;

	map_ini(map, 1);
	fd = open(path, O_RDONLY);
	if (fd < 2)
		terminate(ERR_OPEN);	
	map->map_in_memory = fast_read(fd);
	fast_map_size(map);
	//map_size(path, map);
	//map->points = ft_calloc (map->len, sizeof(t_point));
	//if (map->points == NULL)
	//	terminate(ERR_MEM);
	//fd = open(path, O_RDONLY);
	//if (fd < 2)
	//	terminate(ERR_OPEN);
	// numline = 0;
	// map->len = 0;
	//line = get_next_line(fd);
	// while (map->lines[numline])
	// {
	// 	load_points(map->lines[numline], map, numline + 1);
	// 	numline++;
	// 	//free(line);
	// 	//line = get_next_line(fd);
	// }
	//close(fd);
	go_polar(map);
	ft_printf("\nLoading GUI\n");
}
