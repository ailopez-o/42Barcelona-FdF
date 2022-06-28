#include "../inc/fdf.h"

int load_map(t_map *map)
{

    map->points = malloc(8*sizeof(t_point));
    if (map->points == NULL)
        return (0);
	map->proyect3D = malloc(8*sizeof(t_point));
    if (map->points == NULL)
        return (0);
	map->proyect2D = malloc(8*sizeof(t_point));
    if (map->points == NULL)
        return (0);

	map->len = 8;
	map->scale = 1;
	for (int i = 0; i<8; i++)
		map->points[i].color= FUCSIA;

	map->points[0].axis[x] = -10;
	map->points[0].axis[y] = -10;
	map->points[0].axis[z] = -10;

	map->points[1].axis[x] = 10;
	map->points[1].axis[y] = -10;
	map->points[1].axis[z] = -10;

	map->points[2].axis[x] = 10;
	map->points[2].axis[y] = 10;
	map->points[2].axis[z] = -10;

	map->points[3].axis[x] = -10;
	map->points[3].axis[y] = 10;
	map->points[3].axis[z] = -10;

	map->points[4].axis[x] = -10;
	map->points[4].axis[y] = -10;
	map->points[4].axis[z] = 10;	

	map->points[5].axis[x] = 10;
	map->points[5].axis[y] = -10;
	map->points[5].axis[z] = 10;

	map->points[6].axis[x] = 10;
	map->points[6].axis[y] = 10;
	map->points[6].axis[z] = 10;

	map->points[7].axis[x] = -10;
	map->points[7].axis[y] = 10;
	map->points[7].axis[z] = 10;	

    return (1);
}

void draw_map(t_meta *meta)
{
		generate_background(meta, 0x000000);
		rotate_x(meta->map.points, meta->map.proyect3D, meta->map.ang[x], meta->map.len);
		rotate_y(meta->map.proyect3D, meta->map.proyect3D, meta->map.ang[y], meta->map.len);
		rotate_z(meta->map.proyect3D, meta->map.proyect3D, meta->map.ang[z], meta->map.len);	
		orto_proyection (meta->map.proyect3D, meta->map.proyect2D, meta->map.len);
		scale (meta->map.proyect2D, meta->map.scale, meta->map.len);
		center(meta->map.proyect2D, meta->map.len);

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

}