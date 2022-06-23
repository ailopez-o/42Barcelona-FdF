
#include "../inc/fdf.h"

int draw_bitmap(t_meta *meta, int x0, int y0)
{
    mlx_put_image_to_window(meta->vars.mlx, meta->vars.win, meta->bitmap.img, x0, y0);
}

int draw_line(t_vars *vars, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0	
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
    	mlx_pixel_put(vars->mlx, vars->win, pixelX, pixelY, color);
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

    //image = mlx_new_image(vars->mlx, WINX, WINY);
    //buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
    //printf("PixelBits [%d] - LineBytes [%d] - endian [%d]\n", pixel_bits, line_bytes, endian);
    if (meta->bitmap.bitxpixel != 32)
        color = mlx_get_color_value(meta->vars.mlx, color);
    x = 0;
    y = 0;
    while (y < 1080)
    {
        while(x < 1920)
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
        //printf("Color [%d][%#x] - Buffer [%u][%u][%u]]\n",color, color, buffer[pixel + 0],buffer[pixel + 1], buffer[pixel + 2], buffer[pixel + 3]);
        //draw_line(vars,0,0,1920,y,color);
        if (y%3 == 0) color++;
    }
}