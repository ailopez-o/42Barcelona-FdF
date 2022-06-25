/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:41:08 by aitorlope         #+#    #+#             */
/*   Updated: 2022/05/11 13:13:37 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		len;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_memcpy(s2, s1, len);
	return (s2);
}
