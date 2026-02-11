/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:42:28 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/14 18:54:24 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}
/*
int	main(void)
{
	int		fd;
	int 	cl;
	char	c = 'A';

	fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
	
	if (fd < 0)
		return (1);
	
	ft_putchar_fd(c, fd);

	cl = close(fd);
	if (cl < 0)
		return (1);
	
	return (0);
}*/