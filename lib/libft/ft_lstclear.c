/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 22:58:43 by aitorlope         #+#    #+#             */
/*   Updated: 2022/05/18 00:12:44 by aitorlope        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{	
	t_list	*elem;
	t_list	*temp;

	elem = *lst;
	while (elem)
	{	
		temp = elem->next;
		del(elem->content);
		free(elem);
		elem = temp;
	}
	*lst = NULL;
}
