
#include "../inc/fdf.h"

void draw_bitmap(t_meta *meta, int x0, int y0)
{
    mlx_put_image_to_window(meta->vars.mlx, meta->vars.win, meta->bitmap.img, x0, y0);
}

void my_putpixel(t_meta *meta, t_point pixel)
{
    int mypixel;
    //Calculo la posicion en el buffer;
    mypixel = ((int)pixel.axis[y] * meta->vars.winX * 4) + ((int)pixel.axis[x] * 4);
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



int draw_line(t_meta *meta, t_point start, t_point end)
{
    t_point     delta;
    t_point     pixel;
	int         pixels;

    delta.axis[x] = end.axis[x] - start.axis[x];
    delta.axis[y] = end.axis[y] - start.axis[y];
    pixels = sqrt((delta.axis[x] * delta.axis[x]) + (delta.axis[y] * delta.axis[y]));
	delta.axis[x] /= pixels; 
	delta.axis[y] /= pixels; 
	pixel.axis[x] = start.axis[x];
	pixel.axis[y] = start.axis[y];
    pixel.color = start.color;
	while (pixels)
	{
    	my_putpixel(meta, pixel);
    	pixel.axis[x] += delta.axis[x];
    	pixel.axis[y] += delta.axis[y];
    	--pixels;
	}
	return(1);
}

/*
int draw_line(t_meta *meta, t_line line)
{
    t_point     delta;
    t_point     pixel;
	int         pixels;

    delta.axis[x] = line.end.axis[x] - line.start.axis[x];
    delta.axis[y] = line.end.axis[y] - line.start.axis[y];
    pixels = sqrt((delta.axis[x] * delta.axis[x]) + (delta.axis[y] * delta.axis[y]));
	delta.axis[x] /= pixels; 
	delta.axis[y] /= pixels; 
	pixel.axis[x] = line.start.axis[x];
	pixel.axis[y] = line.start.axis[y];
    pixel.color = line.start.color;
	while (pixels)
	{
    	my_putpixel(meta, pixel);
    	pixel.axis[x] += delta.axis[x];
    	pixel.axis[y] += delta.axis[y];
    	--pixels;
	}
	return(1);
}
*/

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
    int X;
    int Y;
    int pixel;

    if (meta->bitmap.bitxpixel != 32)
        color = mlx_get_color_value(meta->vars.mlx, color);
    X = 0;
    Y = 0;
    while (Y < meta->vars.winY)
    {
        while(X < meta->vars.winX)
        {
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
        //if (y%3 == 0) color++;
    }
}


// Esta funcion multiplica una coordenada por la correspondiente matriz
t_point mul_mat(float matrix[3][3], t_point point) 
{
    int i;
    int k;
    t_point result;

    i = 0;
    while (i < 3)
    {
        result.axis[i] = 0;
        result.color = point.color;
        k = 0;
        while (k < 3)
        {
            result.axis[i] += matrix[i][k] * point.axis[k];
            k++;
        }
    i++;
    }
    return (result);
}


void rotate_x(t_point *points, t_point *proyection, float ang, int len)
{
    int     i;
    float   rad;
    rad = (ang * 3.14159) / 180;
    float   proyect_matrix[3][3] = {
        {1, 0, 0},
        {0, cos(rad), -sin(rad)},
        {0, sin(rad), cos(rad)}
    };

    i = 0;
    while (i < len)
    {
        proyection[i] = mul_mat(proyect_matrix, points[i]);
        i++;
    }
}

void rotate_y(t_point *points, t_point *proyection, float ang, int len)
{
    int     i;
    float   rad;
    rad = (ang * 3.14159) / 180;
    float   proyect_matrix[3][3] = {
        {cos(rad), 0, sin(rad)},
        {0, 1, 0},
        {-(sin(rad)), 0, cos(rad)}
    };

    i = 0;
    while (i < len)
    {
        proyection[i] = mul_mat(proyect_matrix, points[i]);
        i++;
    }
}

void rotate_z(t_point *points, t_point *proyection, float ang, int len)
{
    int     i;
    float   rad;
    rad = (ang * 3.14159) / 180;
    float   proyect_matrix[3][3] = {
        {cos(rad), -sin(rad), 0},
        {sin (rad), cos(rad), 0},
        {0, 0, 1}
    };
    i = 0;
    while (i < len)
    {
        proyection[i] = mul_mat(proyect_matrix, points[i]);
        i++;
    }
}

void traslate(t_point *points, t_point move, int len)
{
    int     i;
    i = 0;
    while (i < len)
    {
        points[i].axis[x] = points[i].axis[x] + move.axis[x];
        points[i].axis[y] = points[i].axis[y] + move.axis[y];
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
        i++;
    }
}

void orto_proyection(t_point *points, t_point *proyection, int len)
{
    int     i;
    float   proyect_matrix[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    i = 0;
    while (i < len)
    {
        proyection[i] = mul_mat(proyect_matrix, points[i]);
        i++;
    }
}