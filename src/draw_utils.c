/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:09:51 by aitorlope         #+#    #+#             */
/*   Updated: 2022/07/10 21:09:56 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../lib/miniliblx/minilibx_macos/mlx.h"
#include "../inc/defines.h"
#include "../inc/utils.h"
#include <math.h>

#define R(a) (a) >> 16
#define G(a) ((a) >> 8) & 0xFF
#define B(a) (a) & 0xFF
#define RGB(a, b, c) ((a) << 16) + ((b) << 8) + (c)

/*
*      endian = 1 --> Most significant (Alpha) byte first
*      endian = 0 --> Least significant (Blue) byte first
*/

void    set_color(char *buffer, int endian, int color, int alpha)
{
    if (endian == 1)   
    {
        buffer[0] = alpha;
        buffer[1] = (color >> 16) & 0xFF;
        buffer[2] = (color >> 8) & 0xFF;
        buffer[3] = (color) & 0xFF;
    }
    else   
    {
        buffer[0] = (color) & 0xFF;
        buffer[1] = (color >> 8) & 0xFF;
        buffer[2] = (color >> 16) & 0xFF;
        buffer[3] = alpha;
    }
}

static int my_putpixel(t_meta *meta, t_point pixel)
{
    int mypixel;
    int alpha;

    alpha = 0;   
    if (pixel.axis[X] < MENU_WIDTH)
        alpha = -10;  
    if(pixel.axis[X] >= WINX || pixel.axis[Y] >= WINY || pixel.axis[X] < 0 || pixel.axis[Y] < 0)
        return (-1);
    mypixel = ((int)pixel.axis[Y] * WINX * 4) + ((int)pixel.axis[X] * 4);
    if (meta->bitmap.bitxpixel != 32)
        pixel.color = mlx_get_color_value(meta->vars.mlx, pixel.color);
    set_color(&meta->bitmap.buffer[mypixel], meta->bitmap.endian, pixel.color, alpha);  
    return(0);
}

void draw_dot(t_meta *meta, t_point point, int radius)
{
    int         x = radius;
    int         y = 0;
    int         xChange = 1 - (radius << 1);
    int         yChange = 0;
    int         radiusError = 0;
    t_point     pixel;

    pixel.color = point.color;
    while (x >= y)
    {
        for (int i = point.axis[X] - x; i <= point.axis[X] + x; i++)
        {
            pixel.axis[X] = i;
            pixel.axis[Y] = (int)point.axis[Y] + y;
            my_putpixel(meta, pixel);
            pixel.axis[X] = i;
            pixel.axis[Y] = (int)point.axis[Y] - y;
            my_putpixel(meta, pixel);  
        }
        for (int i = point.axis[X] - y; i <= point.axis[X] + y; i++)
        {
            pixel.axis[X] = i;
            pixel.axis[Y] = (int)point.axis[Y] + x;
            my_putpixel(meta, pixel);
            pixel.axis[X]= i;
            pixel.axis[Y] = (int)point.axis[Y] - x;
            my_putpixel(meta, pixel);    
        }
        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}

int gradient(int startcolor, int endcolor, int len, int pix)
{
    double increment[3];
    int new[3];
    int newcolor;

    increment[0] = (double)((R(endcolor)) - (R(startcolor))) / (double)len;
    increment[1] = (double)((G(endcolor)) - (G(startcolor))) / (double)len;
    increment[2] = (double)((B(endcolor)) - (B(startcolor))) / (double)len;
    new[0] = (R(startcolor)) + ft_round(pix * increment[0]);
    new[1] = (G(startcolor)) + ft_round(pix * increment[1]);
    new[2] = (B(startcolor)) + ft_round(pix * increment[2]);
    newcolor = RGB(new[0], new[1], new[2]);
    return (newcolor);
}

int valid_pixel(t_point pixel)
{

    if (pixel.axis[X] < 0 || pixel.axis[X] > WINX)
        return (0);
    if (pixel.axis[Y] < 0 || pixel.axis[Y] > WINY)
        return (0);
    return (1);
}


int draw_line(t_meta *meta, t_point start, t_point end)
{
    t_point     delta;
    t_point     pixel;
	int         pixels;
    int         len;

    if (valid_pixel(start) == 0 && valid_pixel(end) == 0)
        return (0);
    delta.axis[X] = end.axis[X] - start.axis[X];
    delta.axis[Y] = end.axis[Y] - start.axis[Y];
    pixels = sqrt((delta.axis[X] * delta.axis[X]) + (delta.axis[Y] * delta.axis[Y]));
    len = pixels;
	delta.axis[X] /= pixels; 
	delta.axis[Y] /= pixels; 
	pixel.axis[X] = start.axis[X];
	pixel.axis[Y] = start.axis[Y];
    pixel.color = start.color;
	while (pixels > 0)
	{
        pixel.color = gradient(start.color, end.color, len, len - pixels);
    	my_putpixel(meta, pixel);
    	pixel.axis[X] += delta.axis[X];
    	pixel.axis[Y] += delta.axis[Y];
        pixels = pixels - 1;
	}
	return(1);
}

void generate_background(t_meta *meta, int backcolor, int menucolor)
{
    int x;
    int y;
    int pixel;
    int color;

    if (meta->bitmap.bitxpixel != 32)
        backcolor = mlx_get_color_value(meta->vars.mlx, backcolor);
    if (meta->bitmap.bitxpixel != 32)
        menucolor = mlx_get_color_value(meta->vars.mlx, menucolor);       
    x = 0;
    y = 0;
    while (y < WINY)
    {
        while(x < WINX )
        {
            if (x < MENU_WIDTH)
                color = menucolor;
            else    
                color = backcolor;
            pixel = (y * meta->bitmap.lines) + (x * 4);
            set_color(&meta->bitmap.buffer[pixel], meta->bitmap.endian, color, 1); 
            x++;
        }
        y++;
        x = 0;
    }
}
