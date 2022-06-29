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

void load_line(char *line, t_map *map)
{

}

int load_map(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		load_line(line, map);
		line = get_next_line(fd);
	}

    map->points = malloc(12*sizeof(t_point));
    if (map->points == NULL)
        return (0);
	map->proyect3D = malloc(12*sizeof(t_point));
    if (map->points == NULL)
        return (0);
	map->proyect2D = malloc(12*sizeof(t_point));
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
	/*
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

void draw_map(t_meta *meta)
{
		meta->map.renders = meta->map.renders + 1;
		
		generate_background(meta, 0x000000);
		rotate_x(meta->map.points, meta->map.proyect3D, meta->map.ang[x], meta->map.len);
		rotate_y(meta->map.proyect3D, meta->map.proyect3D, meta->map.ang[y], meta->map.len);
		rotate_z(meta->map.proyect3D, meta->map.proyect3D, meta->map.ang[z], meta->map.len);	
		orto_proyection (meta->map.proyect3D, meta->map.proyect2D, meta->map.len);
		scale (meta->map.proyect2D, meta->map.scale, meta->map.len);
		traslate(meta->map.proyect2D, meta->map.source, meta->map.len);
		/*
		i = 0;
		while (i < 8)
		{
			meta->map.proyect2D[i].color = FUCSIA;
			draw_dot(meta, meta->map.proyect2D[i], 1);
			i++;
		}
		*/

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
		
		draw_bitmap(meta, 0, 0);	
		draw_menu(meta);
}
