#include "../inc/fdf.h"


void traslate(t_point *points, t_point move, int len)
{
    int     i;
    i = 0;
    while (i < len)
    {
        points[i].axis[x] = points[i].axis[x] + move.axis[x];
        points[i].axis[y] = points[i].axis[y] + move.axis[y];
        points[i].axis[z] = points[i].axis[z] + move.axis[z];
        i++;
    }
}

void center(t_point *points, int len)
{
    int     i;
    i = 0;
    while (i < len)
    {
        points[i].axis[x] = points[i].axis[x] + WINX/2;
        points[i].axis[y] = points[i].axis[y] + WINY/2;
        i++;
    }
}


void scale(t_point *points, int scale, int len)
{
    int     i;
    i = 0;
    while (i < len)
    {
        points[i].axis[x] = points[i].axis[x] * scale;
        points[i].axis[y] = points[i].axis[y] * scale;
        points[i].axis[z] = points[i].axis[z] * scale;
        i++;
    }
}

void isometric(t_map *map)
{
    map->ang[x] = 45;
    map->ang[y] = 30;
}