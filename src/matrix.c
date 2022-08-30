/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:02:13 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/29 16:02:18 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/defines.h"
#include "../inc/utils.h"
#include <math.h>

/*
*   Multiply a 3 points coordinate "point" by Matrix [3][3]
*   and return the result.
*/

t_point	mul_mat(float matrix[3][3], t_point point)
{
	int		i;
	int		k;
	t_point	result;

	result = point;
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

/*
*   Calculate len "points" of the array with the "ang" rotation in X axis
*   and store in "proyection" array.
*/

void	rotate_x(t_point *points, t_point *proyection, float ang, int len)
{
	int		i;
	float	rad;
	float	proyect_matrix[3][3];

	rad = ang * M_PI / 180;
	matrix_init(proyect_matrix);
	proyect_matrix[0][0] = 1;
	proyect_matrix[1][1] = cos(rad);
	proyect_matrix[1][2] = -sin(rad);
	proyect_matrix[2][1] = sin(rad);
	proyect_matrix[2][2] = cos(rad);
	i = 0;
	while (i < len)
	{
		proyection[i] = mul_mat(proyect_matrix, points[i]);
		i++;
	}
}

/*
*   Calculate len "points" of the array with the "ang" rotation in Y axis
*   and store in "proyection" array.
*/

void	rotate_y(t_point *points, t_point *proyection, float ang, int len)
{
	int		i;
	float	rad;
	float	proyect_matrix[3][3];

	rad = ang * M_PI / 180;
	matrix_init(proyect_matrix);
	proyect_matrix[0][0] = cos(rad);
	proyect_matrix[0][2] = sin(rad);
	proyect_matrix[1][1] = 1;
	proyect_matrix[2][0] = -sin(rad);
	proyect_matrix[2][2] = cos(rad);
	i = 0;
	while (i < len)
	{
		proyection[i] = mul_mat(proyect_matrix, points[i]);
		i++;
	}
}

/*
*   Calculate len "points" of the array with the "ang" rotation in Z axis
*   and store in "proyection" array.
*/

void	rotate_z(t_point *points, t_point *proyection, float ang, int len)
{
	int		i;
	float	rad;
	float	proyect_matrix[3][3];

	rad = ang * M_PI / 180;
	matrix_init(proyect_matrix);
	proyect_matrix[0][0] = cos(rad);
	proyect_matrix[0][1] = -sin(rad);
	proyect_matrix[1][0] = sin(rad);
	proyect_matrix[1][1] = cos(rad);
	proyect_matrix[2][2] = 1;
	i = 0;
	while (i < len)
	{
		proyection[i] = mul_mat(proyect_matrix, points[i]);
		i++;
	}
}

/*
*   Calculate len "points" of the array to orto proyection
*   and store in "proyection" array.
*/

void	orto_proyection(t_point *points, t_point *proyection, int len)
{
	int		i;
	float	proyect_matrix[3][3];

	matrix_init(proyect_matrix);
	proyect_matrix[0][0] = 1;
	proyect_matrix[1][1] = 1;
	i = 0;
	while (i < len)
	{
		proyection[i] = mul_mat(proyect_matrix, points[i]);
		i++;
	}
}
