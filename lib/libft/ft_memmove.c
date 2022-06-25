/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:32:15 by aitorlope         #+#    #+#             */
/*   Updated: 2022/05/13 20:25:14 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (len == 0 || dst == src)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst > src)
	{
		while (len)
		{
			*(char *)(dst + len - 1) = *(char *)(src + len - 1);
			len--;
		}
	}	
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
