
#include "../inc/fdf.h"

void draw_bitmap(t_meta *meta, int x0, int y0)
{
    mlx_put_image_to_window(meta->vars.mlx, meta->vars.win, meta->bitmap.img, x0, y0);
}

void my_putpixel(t_meta *meta, t_coord pixel)
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

void draw_dot(t_meta *meta, t_point point, int radius)
{
    int         X = radius;
    int         Y = 0;
    int         xChange = 1 - (radius << 1);
    int         yChange = 0;
    int         radiusError = 0;
    t_coord     pixel;

    pixel.color = point.color;
    while (X >= Y)
    {
        for (int i = point.axis[x] - X; i <= point.axis[x] + X; i++)
        {
            pixel.X = i;
            pixel.Y = point.axis[y] + Y;
            my_putpixel(meta, pixel);
            pixel.X = i;
            pixel.Y = point.axis[y] - Y;
            my_putpixel(meta, pixel);  
        }
        for (int i = point.axis[x] - Y; i <= point.axis[x] + Y; i++)
        {
            pixel.X = i;
            pixel.Y = point.axis[y] + X;
            my_putpixel(meta, pixel);
            pixel.X = i;
            pixel.Y = point.axis[y] - X;
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


// function to multiply two matrices
void multiply_matrix(float first[][10], float second[][10], float result[][10],
                      int r1, int c1, int r2, int c2) {

   // Initializing elements of matrix mult to 0.
   for (int i = 0; i < r1; ++i) {
      for (int j = 0; j < c2; ++j) {
         result[i][j] = 0;
      }
   }

   // Multiplying first and second matrices and storing it in result
   for (int i = 0; i < r1; ++i) {
      for (int j = 0; j < c2; ++j) {
         for (int k = 0; k < c1; ++k) {
            result[i][j] += first[i][k] * second[k][j];
         }
      }
   }
}
 

void mul_mat(float mat1[2][3], float mat2[3][1], float rslt[2][1]) 
{
 
    printf("Multiplication of given two matrices is:\n\n");
 
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 1; j++) {
            rslt[i][j] = 0;
 
            for (int k = 0; k < 3; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
 
            printf("%f\t", rslt[i][j]);
        }
 
        printf("\n");
    }
}


int orto_proyection(t_point *points, t_point *proyection, int len)
{
    int     i;
    float   proyect[2][3] = {
        {1, 0, 0},
        {0, 1, 0}
    };
    float   point[3][1];
    float   proyected[2][1];

    i = 0;
    while (i < len)
    {
        point[0][0] = points[i].axis[x];
        point[1][0] = points[i].axis[y];
        point[2][0] = points[i].axis[z];
        mul_mat(proyect, point, proyected);
        proyection[i].axis[x] =  proyected[0][0];
        proyection[i].axis[y] =  proyected[1][0];
        proyection[i].axis[z] =  0;
        i++;
    }

}