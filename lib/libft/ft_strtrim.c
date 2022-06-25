/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 10:54:46 by ailopez-          #+#    #+#             */
/*   Updated: 2022/05/17 18:23:16 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{	
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (ft_strchr(set, *(s1 + i)) && *s1)
		i++;
	j = ft_strlen(s1);
	while (j > 0 && ft_strchr(set, *(s1 + j)))
		j--;
	if (j == 0)
		return (ft_strdup(""));
	ptr = malloc((j - i + 2) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, (s1 + i), j - i + 2);
	return (ptr);
}
