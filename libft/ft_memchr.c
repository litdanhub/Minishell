/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:42:26 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/15 15:11:17 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t				i;

	if (!s)
		return (NULL);
	str = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char) c)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char *s = "Hello there";
	char c = 'l';
	size_t n =  10;

	printf("My ft_memchr: %s\n", (char *) ft_memchr(s, c, n));
	printf("Libc memchr:  %s\n", (char *) memchr(s, c, n));
	
	return (0);
}*/