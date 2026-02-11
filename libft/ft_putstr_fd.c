/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:55:33 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/14 19:01:46 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
/*
int	main(void)
{
	int		fd;
	int		cl;
	char	*s = "Hello world";

	fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (1);
	ft_putstr_fd(s, fd);
	cl = close(fd);
	if (cl < 0)
		return (1);
	return (0);	
}*/