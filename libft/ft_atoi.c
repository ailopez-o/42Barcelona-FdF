/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:10:54 by ailopez-          #+#    #+#             */
/*   Updated: 2022/05/13 11:28:33 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_isvalid(char caracter)
{
	if (caracter == '\f')
		return (1);
	if (caracter == '\t')
		return (1);
	if (caracter == '\n')
		return (1);
	if (caracter == '\v')
		return (1);
	if (caracter == '\r')
		return (1);
	if (caracter == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	while (ft_isvalid (*(str + i)))
		i++;
	if (*(str + i) == '-')
		neg = -1;
	if (*(str + i) == '+' || *(str + i) == '-')
		i++;
	res = 0;
	while (ft_isdigit((int)*(str + i)))
	{	
		res = (res * 10) + (*(str + i) - '0');
		i++;
	}
	return (res * neg);
}
