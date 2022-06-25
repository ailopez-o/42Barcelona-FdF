/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorlopezdeaudicana <marvin@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:50:37 by aitorlope         #+#    #+#             */
/*   Updated: 2022/05/17 12:20:13 by ailopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h" 

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		ft_putnbr_fd(n, fd);
	}
	else if (n >= 10)
	{		
		ft_putnbr_fd((n / 10), fd);
		digit = (n % 10) + 48;
		write(fd, &digit, 1);
	}
	else
	{
		n = n + 48;
		write(fd, &n, 1);
	}
}
