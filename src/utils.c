
#include "../inc/fdf.h"

int draw_bitmap(t_vars *vars, void *image, int x0, int y0)
{
    mlx_put_image_to_window(vars->mlx, vars->win, image, 0, 0);
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

int colorgrade (int color, int endian)
{
    int newcolor;

    newcolor = color >> 4;
    newcolor++;
    return (newcolor);
}
void draw_line_fast(t_vars *vars, int x0, int y0, int x1, int y1, int color)
{
    void    *image;
    char    *buffer; 
    int     pixel_bits;
    int     line_bytes;
    int     endian;
    int     x;
    int     y;
    int     pixel;

    image = mlx_new_image(vars->mlx, WINX, WINY);
    buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
    printf("PixelBits [%d] - LineBytes [%d] - endian [%d]\n", pixel_bits, line_bytes, endian);
    if (pixel_bits != 32)
        color = mlx_get_color_value(vars->mlx, color);
    x = 0;
    y = 0;
    while (y < 1080)
    {
        while(x < 1920)
        {
            pixel = (y * line_bytes) + (x * 4);
            if (endian == 1)        // Most significant (Alpha) byte first
            {
                buffer[pixel + 0] = (color >> 24);
                buffer[pixel + 1] = (color >> 16) & 0xFF;
                buffer[pixel + 2] = (color >> 8) & 0xFF;
                buffer[pixel + 3] = (color) & 0xFF;
            }
            else if (endian == 0)   // Least significant (Blue) byte first
            {
                buffer[pixel + 0] = (color) & 0xFF;
                buffer[pixel + 1] = (color >> 8) & 0xFF;
                buffer[pixel + 2] = (color >> 16) & 0xFF;
                buffer[pixel + 3] = (color >> 24);
            }
            x++;
        }
        y++;
        x = 0;
        printf("Color [%d][%#x]\n",color, color);
        color = colorgrade(color,0);
    }
    draw_bitmap(vars, image, 0, 0);
}