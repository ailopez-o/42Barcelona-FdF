/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:29:58 by ailopez-          #+#    #+#             */
/*   Updated: 2022/05/10 19:18:00 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	myc;
	char	*lastc;

	myc = (char)c;
	lastc = NULL;
	while (*s != '\0')
	{
		if (*s == myc)
			lastc = (char *)s;
		s++;
	}
	if (myc == '\0')
		return ((char *)s);
	return (lastc);
}
