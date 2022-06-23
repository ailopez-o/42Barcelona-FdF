/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:11:02 by aitorlope         #+#    #+#             */
/*   Updated: 2022/05/16 15:47:35 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	ft_numwrds(char const *s, char c)
{
	int	i;
	int	numwrd;

	i = 0;
	numwrd = 0;
	if (*s != c)
		numwrd ++;
	while (*(s + i))
	{
		if (*(s + i) == c && *(s + i + 1) != c && *(s + i + 1))
			numwrd++;
		i++;
	}
	return (numwrd + 1);
}

char	**ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

char	**gosplit(char **ptrtable, const char *s, char c)
{
	int	first;	
	int	numwrd;

	first = 1;
	numwrd = 0;
	while (*s)
	{	
		if (*s == c || first)
		{
			first = 0;
			while (*s == c)
				s++;
			if (*s)
			{
				ptrtable[numwrd] = ft_substr(s, 0, ft_strchr(s, c) - s);
				if (ptrtable[numwrd] == NULL)
					return (ft_free(ptrtable));
				numwrd++;
			}
		}
		else
			s++;
	}
	ptrtable[numwrd] = NULL;
	return (ptrtable);
}

char	**ft_split(char const *s, char c)
{
	char	**ptrtable;

	ptrtable = (char **)malloc(ft_numwrds(s, c) * sizeof(char *));
	if (ptrtable == NULL)
		return (NULL);
	return (gosplit(ptrtable, s, c));
}
