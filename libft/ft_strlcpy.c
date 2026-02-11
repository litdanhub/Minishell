/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:30:19 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 12:38:39 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
int	main(void)
{
	char dst[20] = "Hello hello";
	char dst1[20] = "Hello hello";

	char *src = "world12345";
	size_t size = 5;

	printf("Return of my ft_strlcpy: %zu\n", ft_strlcpy(dst, src, size));
	printf("%s\n", dst);

	printf("BSD ft_strlcpy: %zu\n", strlcpy(dst1, src, size));
	printf("%s\n", dst1);
	
	return (0);
}*/