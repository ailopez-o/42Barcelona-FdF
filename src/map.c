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
	printf("\nMapa Leido [%d][%d][%d][%d] - SIZE[%d] \n", (int)map->limits.axis[x], (int)map->limits.axis[y], (int)map->limits.axis[z],map->zmin, map->len);	
}

void	load_color (int max, int min, t_point *point, t_colors	colors)
{

	point->color = DEFAULT_COLOR;
	if (point->axis[z] == max)
		point->color = colors.topcolor;
	else if (point->axis[z] == 0)
		point->color = colors.groundcolor;
	else if (point->axis[z] == min && min !=0)
		point->color = colors.bottomcolor;
	else if (point->axis[z] > 0)
		point->color = gradient(colors.groundcolor, colors.topcolor, max, point->axis[z]);
	else
		point->color = gradient(colors.bottomcolor, colors.groundcolor, -min, - (min - point->axis[z]));

}

void	load_points(char *line, t_map *map, int numline)
{

	char	**splited;
	char	**color;
	int		i;

	write(1,".",1);
	splited = ft_split(line, ' ');
	i = 0;
	while (splited[i])
	{
		map->points[map->len].axis[z] = ft_atoi(&splited[i][0]);
		map->points[map->len].axis[x] = i - map->limits.axis[x]/2;
		map->points[map->len].axis[y] = numline - map->limits.axis[y]/2;
		load_color((int)map->limits.axis[z], map->zmin, &map->points[map->len], map->colors);	
		if (ft_strchr(splited[i], ',') != 0)
		{
			dbl_free(color);
			color = ft_split(splited[i], ',');
			map->points[map->len].color  = strtol(color[1] + 2, NULL, 16);
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
	return(i);
}

void	map_size(int fd, t_map *map)
{
	char	*line;
	int		i;
	char 	**splited;
	int		valor;

	map->len = 0;
	map->limits.axis[y] = 0;
	map->limits.axis[z] = 0;
	map->zmin = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		write(1,"*",1);
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
	map->source.axis[x] = WINX/2;
	map->source.axis[y] = WINY/2;	
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

int load_map(t_map *map, char *path)
{	
	int		fd;
	char	*line;
	int 	numline;

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

	return(1);
}

void	draw_controls(t_meta *meta)
{
	char	*str;

	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX, TEXT_COLOR, "//// CONTROLS ////");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + LINE_SIZE * 2, TEXT_COLOR, "Scroll: Zom In/Out");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + LINE_SIZE * 3, TEXT_COLOR, "Left Click: Rotate X/Y axis");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + LINE_SIZE * 4, TEXT_COLOR, "Arrows: Rotate X/Y axis");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + LINE_SIZE * 5, TEXT_COLOR, "Q/W: Rotate Z axis");	
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, CONTROL_BOX + LINE_SIZE * 6, TEXT_COLOR, "Right Click: Move");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX, TEXT_COLOR, "//// MAP INFO ////");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + LINE_SIZE * 2, TEXT_COLOR, "Size:");	
	str = ft_itoa(meta->map.len);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, MAPINFO_BOX + LINE_SIZE * 2, TEXT_COLOR, str);		
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + LINE_SIZE * 3, TEXT_COLOR, "X:");	
	str = ft_itoa(meta->map.limits.axis[x]);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, MAPINFO_BOX + LINE_SIZE * 3, TEXT_COLOR, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + LINE_SIZE * 4, TEXT_COLOR, "Y:");	
	str = ft_itoa(meta->map.limits.axis[y]);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, MAPINFO_BOX + LINE_SIZE * 4, TEXT_COLOR, str);	
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + LINE_SIZE * 5, TEXT_COLOR, "Z:");	
	str = ft_itoa(meta->map.limits.axis[z]);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, MAPINFO_BOX + LINE_SIZE * 5, TEXT_COLOR, str);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, MAPINFO_BOX + LINE_SIZE * 6, TEXT_COLOR, "Zmin:");
	str = ft_itoa(meta->map.zmin);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 78, MAPINFO_BOX + LINE_SIZE * 6, TEXT_COLOR, str);			
	free(str);
}

void draw_menu(t_meta *meta)
{
	char	*str;

	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, DRAWINFO_BOX, TEXT_COLOR, "//// DRAW INFO ////");
	str = ft_itoa(meta->map.renders);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, DRAWINFO_BOX + LINE_SIZE * 2, TEXT_COLOR, "Reenders:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 100, DRAWINFO_BOX + LINE_SIZE * 2, TEXT_COLOR, str);
	str = ft_itoa(meta->map.ang[x]);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, DRAWINFO_BOX + LINE_SIZE * 3, TEXT_COLOR, "X Axis:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, DRAWINFO_BOX + LINE_SIZE * 3, TEXT_COLOR, str);
	str = ft_itoa(meta->map.ang[y]);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, DRAWINFO_BOX + LINE_SIZE * 4, TEXT_COLOR, "Y Axix:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, DRAWINFO_BOX + LINE_SIZE * 4, TEXT_COLOR, str);
	str = ft_itoa(meta->map.ang[z]);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, DRAWINFO_BOX + LINE_SIZE * 5, TEXT_COLOR, "Z Axix:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, DRAWINFO_BOX + LINE_SIZE * 5, TEXT_COLOR, str);
	str = ft_itoa(meta->map.scale);
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB, DRAWINFO_BOX + LINE_SIZE * 6, TEXT_COLOR, "Zoom:");
	mlx_string_put(meta->vars.mlx, meta->vars.win, MENU_TAB + 80, DRAWINFO_BOX + LINE_SIZE * 6, TEXT_COLOR, str);	
	free(str);
	draw_controls(meta);
}

void	wired(t_meta *meta, t_point *wire)
{
	int i;

	i = 0;
	while (i < meta->map.len)
	{
		if ((i + 1)%(int)meta->map.limits.axis[x] != 0)
			draw_line(meta, wire[i], wire[i + 1]);
		if ((i/(int)meta->map.limits.axis[x]) != (meta->map.limits.axis[y] - 1))
			draw_line(meta, wire[i], wire[i + (int)meta->map.limits.axis[x]]);
		i++;
	}
}

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

int draw_map(t_meta *meta)
{
	t_point		*proyect;

	proyect = malloc (meta->map.len * sizeof(t_point));
	if (proyect == NULL)
		return (-1);
	meta->map.renders = meta->map.renders + 1;
	generate_background(meta, meta->map.colors.backcolor, meta->map.colors.menucolor);
	rotate_x(meta->map.points, proyect, meta->map.ang[x], meta->map.len);
	rotate_y(proyect, proyect, meta->map.ang[y], meta->map.len);
	rotate_z(proyect, proyect, meta->map.ang[z], meta->map.len);	
	orto_proyection (proyect, proyect, meta->map.len);
	scale (proyect, meta->map.scale, meta->map.len);
	traslate(proyect, meta->map.source, meta->map.len);		
	if (meta->map.b_lines)
		wired(meta, proyect);
	if (meta->map.b_dots)
		doted(meta,proyect);
	draw_bitmap(meta, 0, 0);	
	draw_menu(meta);
	free (proyect);
	return(1);
}
