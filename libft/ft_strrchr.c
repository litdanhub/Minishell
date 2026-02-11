/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:04:54 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/15 16:57:33 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if ((unsigned char) c == '\0' && s[i] == '\0')
		return ((char *) &s[i]);
	while (i >= 0)
	{
		if (s[i] == (unsigned char) c)
		{
			return ((char *) &s[i]);
		}
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char *s = "Hello world!";
	char c = '\0';

	printf("My ft_strrchr: %s\n", ft_strrchr(s, c));
	printf("Libc strrchr:  %s\n", strrchr(s, c));

	char c1 = 'o';

	printf("My ft_strrchr: %s\n", ft_strrchr(s, c1));
	printf("Libc strrchr:  %s\n", strrchr(s, c1));

	return (0);
}*/