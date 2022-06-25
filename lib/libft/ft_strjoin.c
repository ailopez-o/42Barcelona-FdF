/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:10:37 by ailopez-          #+#    #+#             */
/*   Updated: 2022/05/13 19:58:18 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		lens1;
	int		lens2;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	ptr = malloc (sizeof(char) * (lens1 + lens2 + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, lens1 + 1);
	ft_strlcat(ptr, s2, lens1 + lens2 + 1);
	return (ptr);
}
