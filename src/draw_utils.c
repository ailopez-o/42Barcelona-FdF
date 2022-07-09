#include "../inc/fdf.h"

int my_putpixel(t_meta *meta, t_point pixel)
{
    int mypixel;
    int alpha;

    alpha = 0;   
    if (pixel.axis[x] < MENU_WIDTH)
        alpha = -10;  
    if(pixel.axis[x] >= WINX || pixel.axis[y] >= WINY || pixel.axis[x] < 0 || pixel.axis[y] < 0)
        return (-1);
    //Calculo la posicion en el buffer;
    mypixel = ((int)pixel.axis[y] * WINX * 4) + ((int)pixel.axis[x] * 4);
    if (meta->bitmap.bitxpixel != 32)
        pixel.color = mlx_get_color_value(meta->vars.mlx, pixel.color);
    //Generamos el color
    if (meta->bitmap.endian == 1)        // Most significant (Alpha) byte first
        {
        meta->bitmap.buffer[mypixel + 0] = alpha;
        meta->bitmap.buffer[mypixel + 1] = (pixel.color >> 16) & 0xFF;
        meta->bitmap.buffer[mypixel + 2] = (pixel.color >> 8) & 0xFF;
        meta->bitmap.buffer[mypixel + 3] = (pixel.color) & 0xFF;
        }
    else if (meta->bitmap.endian == 0)   // Least significant (Blue) byte first
    {
        meta->bitmap.buffer[mypixel + 0] = (pixel.color) & 0xFF;
        meta->bitmap.buffer[mypixel + 1] = (pixel.color >> 8) & 0xFF;
        meta->bitmap.buffer[mypixel + 2] = (pixel.color >> 16) & 0xFF;
        meta->bitmap.buffer[mypixel + 3] = alpha;
    }
    return(0);
}

void draw_dot(t_meta *meta, t_point point, int radius)
{
    int         X = radius;
    int         Y = 0;
    int         xChange = 1 - (radius << 1);
    int         yChange = 0;
    int         radiusError = 0;
    t_point     pixel;

    pixel.color = point.color;
    while (X >= Y)
    {
        for (int i = point.axis[x] - X; i <= point.axis[x] + X; i++)
        {
            pixel.axis[x] = i;
            pixel.axis[y] = (int)point.axis[y] + Y;
            my_putpixel(meta, pixel);
            pixel.axis[x] = i;
            pixel.axis[y] = (int)point.axis[y] - Y;
            my_putpixel(meta, pixel);  
        }
        for (int i = point.axis[x] - Y; i <= point.axis[x] + Y; i++)
        {
            pixel.axis[x] = i;
            pixel.axis[y] = (int)point.axis[y] + X;
            my_putpixel(meta, pixel);
            pixel.axis[x]= i;
            pixel.axis[y] = (int)point.axis[y] - X;
            my_putpixel(meta, pixel);    
        }
        Y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            X--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}

int	ft_round(double num)
{
	int rounded;

	rounded = (int)num;
	if (num - rounded >= .5)
		rounded++;
	return (rounded);
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


int draw_line(t_meta *meta, t_point start, t_point end)
{
    t_point     delta;
    t_point     pixel;
	int         pixels;
    int         len;

    delta.axis[x] = end.axis[x] - start.axis[x];
    delta.axis[y] = end.axis[y] - start.axis[y];
    pixels = sqrt((delta.axis[x] * delta.axis[x]) + (delta.axis[y] * delta.axis[y]));
    len = pixels;
	delta.axis[x] /= pixels; 
	delta.axis[y] /= pixels; 
	pixel.axis[x] = start.axis[x];
	pixel.axis[y] = start.axis[y];
    pixel.color = start.color;
	while (pixels)
	{
        pixel.color = gradient(start.color, end.color, len, len - pixels);
    	my_putpixel(meta, pixel);
    	pixel.axis[x] += delta.axis[x];
    	pixel.axis[y] += delta.axis[y];
    	--pixels;
	}
	return(1);
}

t_point set_point(float X, float Y, float Z, int color)
{
    t_point     point;

    point.color = color;
	point.axis[x] = X;
	point.axis[y] = Y;
	point.axis[z] = Z;
    return (point);
}


void generate_background(t_meta *meta, int backcolor, int menucolor)
{
    int X;
    int Y;
    int pixel;
    int color;

    if (meta->bitmap.bitxpixel != 32)
        backcolor = mlx_get_color_value(meta->vars.mlx, backcolor);
    if (meta->bitmap.bitxpixel != 32)
        menucolor = mlx_get_color_value(meta->vars.mlx, menucolor);       
    X = 0;
    Y = 0;
    while (Y < WINY)
    {
        while(X < WINX )
        {
            if (X < MENU_WIDTH)
                color = menucolor;
            else    
                color = backcolor;

            pixel = (Y * meta->bitmap.lines) + (X * 4);
            if (meta->bitmap.endian == 1)        // Most significant (Alpha) byte first
            {
                meta->bitmap.buffer[pixel + 0] = (color >> 24);
                meta->bitmap.buffer[pixel + 1] = (color >> 16) & 0xFF;
                meta->bitmap.buffer[pixel + 2] = (color >> 8) & 0xFF;
                meta->bitmap.buffer[pixel + 3] = (color) & 0xFF;
            }
            else if (meta->bitmap.endian == 0)   // Least significant (Blue) byte first
            {
                meta->bitmap.buffer[pixel + 0] = (color) & 0xFF;
                meta->bitmap.buffer[pixel + 1] = (color >> 8) & 0xFF;
                meta->bitmap.buffer[pixel + 2] = (color >> 16) & 0xFF;
                meta->bitmap.buffer[pixel + 3] = (color >> 24);
            }
            X++;
        }
        Y++;
        X = 0;
    }
}
