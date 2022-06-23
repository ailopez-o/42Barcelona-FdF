
#include "../inc/fdf.h"

void draw_bitmap(t_meta *meta, int x0, int y0)
{
    mlx_put_image_to_window(meta->vars.mlx, meta->vars.win, meta->bitmap.img, x0, y0);
}

int my_putpixel(t_meta *meta, int pixelX, int pixelY, int color)
{
    int pixel;
    //Calculo la posicion en el buffer;
    pixel = (pixelY * meta->vars.winX * 4) + (pixelX * 4);
    if (meta->bitmap.bitxpixel != 32)
        color = mlx_get_color_value(meta->vars.mlx, color);
    //Generamos el color
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
}


int draw_line(t_meta *meta, t_line line)
{
	double deltaX = line.endX - line.beginX; // 10
	double deltaY = line.endY - line.beginY; // 0	
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = line.beginX;
	double pixelY = line.beginY;
	while (pixels)
	{
    	my_putpixel(meta, pixelX, pixelY, line.begincolor);
    	pixelX += deltaX;
    	pixelY += deltaY;
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