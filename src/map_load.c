/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitoraudicana <aitoraudicana@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:26:13 by aitorlope         #+#    #+#             */
/*   Updated: 2023/01/02 17:26:48 by aitoraudica      ###   ########.fr       */
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

#define BLOCK_READ 500000

static	void	map_size(t_map *map);
static	void	map_get_points(t_map *map);
static	char	*fast_read(int fd);

/* 
*	Inicialize the structure
*	Get the map_size
*	Check if the map is valid
*	Read the map
*	Load each point to the structure
*/

void	load_map(t_map *map, char *path)
{
	int	fd;

	map_ini(map, 1);
	fd = open(path, O_RDONLY);
	if (fd < 2)
		terminate(ERR_OPEN);
	map->memory = fast_read(fd);
	close (fd);
	map_size(map);
	map_get_points(map);
	colorize(map);
	go_polar(map);
	ft_printf("\nLoading GUI\n");
}

static char	*fast_read(int fd)
{
	static int	byte_read = BLOCK_READ;
	static int	total_bytes = 0;
	char		*buffer;
	char		*temp;
	char		*map;

	buffer = malloc(BLOCK_READ * sizeof(char));
	if (buffer == NULL)
		terminate(ERR_MEM);
	map = ft_strdup("");
	ft_printf("\n Map loading...\n\n");
	while (byte_read == BLOCK_READ)
	{	
		ft_bzero (buffer, BLOCK_READ);
		byte_read = read(fd, buffer, BLOCK_READ);
		temp = map;
		map = ft_strjoin(map, buffer);
		total_bytes += byte_read;
		ft_printf("\r %d kb reading", total_bytes / 1024);
		free(temp);
	}
	printf("\r ✅ %d kb readed \n", total_bytes / 1024);
	free(buffer);
	return (map);
}

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

	splited = ft_split(line, ' ');
	i = 0;
	while (splited[i] && splited[i][0] != '\n')
	{
		if (!valid_point(&splited[i][0]))
			terminate(ERR_EMPTY);
		map->points[point_index].axis[Z] = ft_atoi(&splited[i][0]);
		map->points[point_index].axis[X] = i - map->limits.axis[X] / 2;
		map->points[point_index].axis[Y] = numline - map->limits.axis[Y] / 2;
		map->points[point_index].paint = 1;
		map->points[point_index].color = DEFAULT_COLOR;
		map->points[point_index].hex_color = has_hexcolors (splited[i]);
		if (map->limits.axis[Z] < map->points[point_index].axis[Z])
			map->limits.axis[Z] = map->points[point_index].axis[Z];
		if (map->zmin > map->points[point_index].axis[Z])
			map->zmin = map->points[point_index].axis[Z];
		i++;
		point_index++;
	}
	dbl_free(splited);
	return (i);
}

/* 
*	This function determinates the max values x, y, z of the map
*	and terminate if the maps has different line sizes.
*/

static	void	map_size(t_map *map)
{
	static int	i = -1;
	static int	num_elems = 0;	

	while (map->memory[++i])
	{
		if (map->memory[i] == '\n' && map->memory[i + 1] == '\0')
			break ;
		if (ft_isalnum(map->memory[i]) && \
			(map->memory[i + 1] == ' ' || map->memory[i + 1] == '\n' || \
			map->memory[i + 1] == '\0'))
				num_elems++;
		if (map->memory[i] == '\n')
		{
			map->limits.axis[Y]++;
			if (map->limits.axis[X] != 0 && (map->limits.axis[X] != num_elems))
				terminate(ERR_LINE);
			else
				map->limits.axis[X] = num_elems;
			num_elems = 0;
		}
	}
	if (num_elems > 0 && (map->limits.axis[X] != num_elems))
		terminate(ERR_LINE);
	map->limits.axis[Y]++;
	map->len = map->limits.axis[X] * map->limits.axis[Y];
}

static	void	map_get_points(t_map *map)
{
	int			i;
	char		*line;
	char		*last_line;
	static int	num_points = 0;
	static int	num_line = 0;

	last_line = map->memory;
	line = NULL;
	i = 0;
	map->points = ft_calloc (map->len, sizeof(t_point));
	while (++i)
	{
		if (map->memory[i] == '\n' || map->memory[i] == '\0')
		{
			free (line);
			line = ft_substr(last_line, 0, &map->memory[i] - last_line);
			last_line = &map->memory[i + 1];
			num_points += load_points(line, map, num_line++);
			ft_printf("\r ▶ %d points reading...", num_points);
			if (map->memory[i] == '\0')
				break ;
		}
	}
	free (line);
	ft_printf("\r ✅ %d points readed\n", num_points);
}
