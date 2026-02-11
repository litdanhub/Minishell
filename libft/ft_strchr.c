/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:46:01 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 12:24:44 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *) &s[i]);
	return (NULL);
}
/*
int	main(void)
{
	const char *s = "Hello world!";
	char c = 'w';
	printf("My ft_strchr: %s\n", ft_strchr(s, c));
	printf("Libc strchr:  %s\n", strchr(s, c));

	c = '\0';
	printf("My ft_strchr: %s\n", ft_strchr(s, c));
	printf("Libc strchr:  %s\n", strchr(s, c));

	return (0);
}*/