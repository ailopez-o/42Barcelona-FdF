
#include "../inc/fdf.h"

void draw_bitmap(t_meta *meta, int x0, int y0)
{
    mlx_put_image_to_window(meta->vars.mlx, meta->vars.win, meta->bitmap.img, x0, y0);
}

int my_putpixel(t_meta *meta, t_coord pixel)
{
    int mypixel;
    //Calculo la posicion en el buffer;
    mypixel = (pixel.Y * meta->vars.winX * 4) + (pixel.X * 4);
    if (meta->bitmap.bitxpixel != 32)
        pixel.color = mlx_get_color_value(meta->vars.mlx, pixel.color);
    //Generamos el color
    if (meta->bitmap.endian == 1)        // Most significant (Alpha) byte first
        {
        meta->bitmap.buffer[mypixel + 0] = (pixel.color >> 24);
        meta->bitmap.buffer[mypixel + 1] = (pixel.color >> 16) & 0xFF;
        meta->bitmap.buffer[mypixel + 2] = (pixel.color >> 8) & 0xFF;
        meta->bitmap.buffer[mypixel + 3] = (pixel.color) & 0xFF;
        }
    else if (meta->bitmap.endian == 0)   // Least significant (Blue) byte first
    {
        meta->bitmap.buffer[mypixel + 0] = (pixel.color) & 0xFF;
        meta->bitmap.buffer[mypixel + 1] = (pixel.color >> 8) & 0xFF;
        meta->bitmap.buffer[mypixel + 2] = (pixel.color >> 16) & 0xFF;
        meta->bitmap.buffer[mypixel + 3] = (pixel.color >> 24);
    }
}

void draw_dot(t_meta *meta, t_coord pos, int radius)
{
    int         x = radius;
    int         y = 0;
    int         xChange = 1 - (radius << 1);
    int         yChange = 0;
    int         radiusError = 0;
    t_coord     pixel;

    pixel.color = pos.color;
    while (x >= y)
    {
        for (int i = pos.X - x; i <= pos.X + x; i++)
        {
            pixel.X = i;
            pixel.Y = pos.Y + y;
            my_putpixel(meta, pixel);
            pixel.X = i;
            pixel.Y = pos.Y - y;
            my_putpixel(meta, pixel);  
        }
        for (int i = pos.X - y; i <= pos.X + y; i++)
        {
            pixel.X = i;
            pixel.Y = pos.Y + x;
            my_putpixel(meta, pixel);
            pixel.X = i;
            pixel.Y = pos.Y - x;
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


int draw_line(t_meta *meta, t_line line)
{
    t_coord     pixeldraw;
    t_pcoord    delta;
    t_pcoord    pixel;
	int     pixels;

    delta.X = line.end.X - line.start.X;
    delta.Y = line.end.Y - line.start.Y;
    pixels = sqrt((delta.X * delta.X) + (delta.Y * delta.Y));
	delta.X /= pixels; 
	delta.Y /= pixels; 
	pixel.X = line.start.X;
	pixel.Y = line.start.Y;
	while (pixels)
	{
        pixeldraw.X = (int)pixel.X;
        pixeldraw.Y = (int)pixel.Y;
        pixeldraw.color = line.start.color;
    	my_putpixel(meta, pixeldraw);
    	pixel.X += delta.X;
    	pixel.Y += delta.Y;
    	--pixels;
	}
	return(1);
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
void generate_background(t_meta *meta, int color)
{
    int x;
    int y;
    int pixel;

    if (meta->bitmap.bitxpixel != 32)
        color = mlx_get_color_value(meta->vars.mlx, color);
    x = 0;
    y = 0;
    while (y < meta->vars.winY)
    {
        while(x < meta->vars.winX)
        {
            pixel = (y * meta->bitmap.lines) + (x * 4);
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
            x++;
        }
        y++;
        x = 0;
        //if (y%3 == 0) color++;
    }
}