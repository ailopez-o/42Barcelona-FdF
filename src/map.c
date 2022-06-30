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

void	print_points(t_map *map)
{
	int i;

	i = 0;
	printf("Mapa Leido [%d][%d][%d] - SIZE[%d] \n", (int)map->limits.axis[x], (int)map->limits.axis[y], (int)map->limits.axis[z], map->len);	
	while (i < map->len)
	{
		printf(" POINT(%d) [%d][%d][%d] - COLOR [%x]\n", i,(int)map->points[i].axis[x], (int)map->points[i].axis[y], (int)map->points[i].axis[z],map->points[i].color);
		i++;
	}
}

void	colorize(t_map *map)
{

	printf("Mapa Leido [%d][%d][%d][%d] - SIZE[%d] \n", (int)map->limits.axis[x], (int)map->limits.axis[y], (int)map->limits.axis[z],map->zmin, map->len);	
}

void	load_points(char *line, t_map *map, int numline)
{

	char	**splited;
	char	**color;
	int		i;

	splited = ft_split(line, ' ');
	i = 0;
	while (splited[i])
	{
		map->points[map->len].axis[z] = ft_atoi(&splited[i][0]);
		if (map->limits.axis[z] < map->points[map->len].axis[z])
			map->limits.axis[z] = map->points[map->len].axis[z];
		if (map->zmin > map->points[map->len].axis[z])
			map->zmin = map->points[map->len].axis[z];		
		map->points[map->len].axis[x] = i - map->limits.axis[x]/2;
		map->points[map->len].axis[y] = numline - map->limits.axis[y]/2;
		map->points[map->len].color = DEFAULT_COLOR;	
		if (map->points[map->len].axis[z] == map->limits.axis[z])
			map->points[map->len].color = TOP_COLOR;
		if (map->points[map->len].axis[z] == 0)
			map->points[map->len].color = GROUND_COLOR;			
		if (map->points[map->len].axis[z] == map->zmin)
			map->points[map->len].color = GROUND_COLOR;				
		if (ft_strchr(splited[i], ',') != 0)
		{
			color = ft_split(splited[i], ',');
			map->points[map->len].color  = strtol(color[1] + 2, NULL, 16);
			//ap->points[map->len].color = TOP_COLOR;
		}
		i++;
		map->len++;
	}
}

int	line_size(char *line)
{
	int		i;
	char	**split;

	split = ft_split(line, ' ');
	i = 0;
	while (split[i])
		i++;
	return(i);
}

void	map_size(int fd, t_map *map)
{
	char	*line;

	map->len = 0;
	map->limits.axis[y] = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->limits.axis[x] = line_size(line);
		map->len += map->limits.axis[x];
		map->limits.axis[y]++;
		line = get_next_line(fd);
	}
}

int load_map(t_map *map, char *path)
{	
	int		fd;
	char	*line;
	int 	numline;

	fd = open(path, O_RDONLY);
	if (fd < 2)
		return (-1);
	map_size(fd, map);
	map->points = malloc (map->len * sizeof(t_point));
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
		line = get_next_line(fd);
	}
	colorize(map);
	map->renders = 0;
	map->scale = 1;	
	map->source.axis[x] = WINX/2;
	map->source.axis[y] = WINY/2;	
	map->source.axis[z] = 0;
	map->ang[x] = 0;
	map->ang[y] = 0;
	map->ang[z] = 0;	
	return(1);
/*


    map->points = malloc(12*sizeof(t_point));
    if (map->points == NULL)
        return (0);

	map->renders = 0;
	map->len = 8;
	map->scale = 1;
	map->source.axis[x] = WINX/2;
	map->source.axis[y] = WINY/2;	
	map->source.axis[z] = 0;

	for (int i = 0; i < map->len; i++)
		map->points[i].color= FUCSIA;

	map->points[0].axis[x] = -10;
	map->points[0].axis[y] = -10;
	map->points[0].axis[z] = -10;
	map->points[0].color = VERDE;

	map->points[1].axis[x] = 10;
	map->points[1].axis[y] = -10;
	map->points[1].axis[z] = -10;

	map->points[2].axis[x] = 10;
	map->points[2].axis[y] = 10;
	map->points[2].axis[z] = -10;

	map->points[3].axis[x] = -10;
	map->points[3].axis[y] = 10;
	map->points[3].axis[z] = -10;
	map->points[3].color = COLOR_DISCO;

	map->points[4].axis[x] = -10;
	map->points[4].axis[y] = -10;
	map->points[4].axis[z] = 10;	

	map->points[5].axis[x] = 10;
	map->points[5].axis[y] = -10;
	map->points[5].axis[z] = 10;
	map->points[5].color = COLOR_SAFFRON;

	map->points[6].axis[x] = 10;
	map->points[6].axis[y] = 10;
	map->points[6].axis[z] = 10;

	map->points[7].axis[x] = -10;
	map->points[7].axis[y] = 10;
	map->points[7].axis[z] = 10;	

	// EJE DE COORDENADAS

	map->points[8].axis[x] = 0;
	map->points[8].axis[y] = 0;
	map->points[8].axis[z] = 0;	

	map->points[9].axis[x] = 20;
	map->points[9].axis[y] = 0;
	map->points[9].axis[z] = 0;		
	map->points[9].color = ROJO;

	map->points[10].axis[x] = 0;
	map->points[10].axis[y] = 20;
	map->points[10].axis[z] = 0;
	map->points[10].color = VERDE;

	map->points[11].axis[x] = 0;
	map->points[11].axis[y] = 0;
	map->points[11].axis[z] = 20;	
	map->points[11].color = FUCSIA;

*/
    return (1);
}

void draw_menu(t_meta *meta)
{
	char	*str;

	str = ft_itoa(meta->map.renders);
	mlx_string_put(meta->vars.mlx, meta->vars.win, 10, 10, TEXT_COLOR, "Reenders:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, 110, 10, TEXT_COLOR, str);
	str = ft_itoa(meta->map.ang[x]);
	mlx_string_put(meta->vars.mlx, meta->vars.win, 10, 60, TEXT_COLOR, "X Axis:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, 100, 60, TEXT_COLOR, str);
	str = ft_itoa(meta->map.ang[y]);
	mlx_string_put(meta->vars.mlx, meta->vars.win, 10, 90, TEXT_COLOR, "Y Axix:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, 100, 90, TEXT_COLOR, str);
	str = ft_itoa(meta->map.ang[z]);
	mlx_string_put(meta->vars.mlx, meta->vars.win, 10, 120, TEXT_COLOR, "Z Axix:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, 100, 120, TEXT_COLOR, str);
	str = ft_itoa(meta->map.scale);
	mlx_string_put(meta->vars.mlx, meta->vars.win, 10, 150, TEXT_COLOR, "Zoom:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, 100, 150, TEXT_COLOR, str);	
	free(str);
}
void	wired(t_meta *meta, t_point *wire)
{
	int i;

	i = 0;
	while (i < meta->map.len)
	{
		//if (i%(int)meta->map.limits.axis[x] != 0)
		draw_line(meta, wire[i], wire[i + 1]);
		draw_line(meta, wire[i], wire[i + (int)meta->map.limits.axis[x]]);
		i++;
	}
}

void draw_map(t_meta *meta)
{
		int i;
		t_point		*proyect;

		proyect = malloc (meta->map.len * sizeof(t_point));
		//Proteger Malloc
		meta->map.renders = meta->map.renders + 1;
		
		generate_background(meta, 0x000000);
		rotate_x(meta->map.points, proyect, meta->map.ang[x], meta->map.len);
		rotate_y(proyect, proyect, meta->map.ang[y], meta->map.len);
		rotate_z(proyect, proyect, meta->map.ang[z], meta->map.len);	
		orto_proyection (proyect, proyect, meta->map.len);
		scale (proyect, meta->map.scale, meta->map.len);
		traslate(proyect, meta->map.source, meta->map.len);
		


		i = 0;
		while (i < meta->map.len)
		{
			//proyect[i].color = FUCSIA;
			draw_dot(meta, proyect[i], 1);
			i++;
		}
		
//		wired(meta, proyect);

/*
		draw_line(meta, proyect[0], proyect[1]);
		draw_line(meta, proyect[1], proyect[2]);
		draw_line(meta, proyect[2], proyect[3]);
		draw_line(meta, proyect[3], proyect[0]);

		draw_line(meta, proyect[4], proyect[5]);
		draw_line(meta, proyect[5], proyect[6]);	
		draw_line(meta, proyect[6], proyect[7]);
		draw_line(meta, proyect[7], proyect[4]);

		draw_line(meta, proyect[0], proyect[4]);
		draw_line(meta, proyect[1], proyect[5]);
		draw_line(meta, proyect[2], proyect[6]);
		draw_line(meta, proyect[3], proyect[7]);

		draw_line(meta, meta->map.proyect2D[0], meta->map.proyect2D[1]);
		draw_line(meta, meta->map.proyect2D[1], meta->map.proyect2D[2]);
		draw_line(meta, meta->map.proyect2D[2], meta->map.proyect2D[3]);
		draw_line(meta, meta->map.proyect2D[3], meta->map.proyect2D[0]);

		draw_line(meta, meta->map.proyect2D[4], meta->map.proyect2D[5]);
		draw_line(meta, meta->map.proyect2D[5], meta->map.proyect2D[6]);	
		draw_line(meta, meta->map.proyect2D[6], meta->map.proyect2D[7]);
		draw_line(meta, meta->map.proyect2D[7], meta->map.proyect2D[4]);

		draw_line(meta, meta->map.proyect2D[0], meta->map.proyect2D[4]);
		draw_line(meta, meta->map.proyect2D[1], meta->map.proyect2D[5]);
		draw_line(meta, meta->map.proyect2D[2], meta->map.proyect2D[6]);
		draw_line(meta, meta->map.proyect2D[3], meta->map.proyect2D[7]);

		// EJE DE COORDENADAS
		//draw_line(meta, meta->map.proyect2D[9], meta->map.proyect2D[8]);
		//draw_line(meta, meta->map.proyect2D[10], meta->map.proyect2D[8]);
		//draw_line(meta, meta->map.proyect2D[11], meta->map.proyect2D[8]);
	*/
		draw_bitmap(meta, 0, 0);	
		draw_menu(meta);
		free (proyect);
}
