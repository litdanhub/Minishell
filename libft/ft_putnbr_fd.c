/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:42:28 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 11:45:30 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = n;
	if (nb == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	c = nb % 10 + '0';
	write(fd, &c, 1);
}
/* 
int	main(void)
{
	
	int	n = 0;
	//int n = INT_MAX;
	//int n = INT_MIN;
	//int n = 0;
	//int n = -1;
	//int n = 9;
	//int n = 999999;

	ft_putnbr_fd(n, 1);
	
	int	fd;
	int cl;
	fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
	
	if (fd < 0)
		return (1);
	
	ft_putnbr_fd(n, fd);

	cl = close(fd);
	if (cl < 0)
		return (1);
	
	return (0);
}*/