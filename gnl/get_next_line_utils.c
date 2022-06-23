/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:52:00 by ailopez-          #+#    #+#             */
/*   Updated: 2022/06/14 13:52:01 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	i = 0;
	while (i < dstsize)
	{
		if (*(src + i) == '\0')
		{
			*(dst + i) = *(src + i);
			return (len);
		}
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i - 1) = '\0';
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i) != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*str;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[size] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	char	myc;

	myc = (char)c;
	while (*s != '\0' && *s != myc)
		s++;
	if (*s == myc)
		return ((char *)s);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*s1;
	size_t	i;

	s1 = (char *) malloc (count * size);
	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		*(s1 + i) = 0;
		i++;
	}	
	return (s1);
}
