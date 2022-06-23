/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:20:09 by aitorlope         #+#    #+#             */
/*   Updated: 2022/05/16 15:59:33 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_itoalen(char **s, int n)
{
	int		len;
	long	valor;

	len = 0;
	valor = n;
	while (valor)
	{
		valor = valor / 10;
		len++;
	}
	valor = n;
	len++;
	if (valor < 0)
		len++;
	if (valor == 0)
		len = 2;
	*s = malloc(len * sizeof(char));
	return (len);
}

char	*ft_itoa(int n)
{
	long	valor;
	int		len;
	char	*chrnum;

	chrnum = NULL;
	len = ft_itoalen(&chrnum, n);
	if (chrnum == NULL)
		return (NULL);
	valor = n;
	if (valor == 0)
		chrnum[0] = '0';
	if (valor < 0)
	{
		chrnum[0] = '-';
		valor = -valor;
	}
	chrnum[len - 1] = '\0';
	while (valor)
	{
		chrnum[len - 2] = (valor % 10) + 48;
		valor = valor / 10;
		len--;
	}
	return (chrnum);
}
