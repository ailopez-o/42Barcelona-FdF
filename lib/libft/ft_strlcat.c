/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:15:23 by ailopez-          #+#    #+#             */
/*   Updated: 2022/05/11 18:48:01 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize == 0 || dstsize <= dlen)
		return (slen + dstsize);
	i = 0;
	j = dlen;
	while (*(src + i) != '\0' && i < dstsize - dlen - 1)
	{
		*(dst + j) = *(src + i);
		i++;
		j++;
	}
	*(dst + j) = '\0';
	return (dlen + slen);
}
