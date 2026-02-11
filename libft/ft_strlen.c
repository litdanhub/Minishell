/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:41:29 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 12:39:35 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}
/*
int	main(void)
{
	char *c = "Hello world";
	

	printf("My ft_strlen: %zu\n", ft_strlen(c));
	printf("Libc strlen:  %zu\n", strlen(c));
	
	return (0);
}*/