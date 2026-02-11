/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:55:33 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/14 19:02:59 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
/*
int	main(void)
{
	int		fd;
	int		cl;
	char	*s = "Hello world";

	fd = open("test.txt", O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		return (1);
	ft_putendl_fd(s, fd);
	cl = close(fd);
	if (cl < 0)
		return (1);
	return (0);	
}*/