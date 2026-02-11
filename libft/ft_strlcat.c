/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:57:34 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 12:38:28 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size && dst[i])
		i++;
	if (i == size)
		return (size + ft_strlen(src));
	j = 0;
	while (j < size - i - 1 && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i + j < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
int	main(void)
{
	char dst[20] = "Hello ";
	char dst1[20] = "Hello ";
	
	char *src = "world";
	size_t size = 5;

	printf("Return of my ft_strlcat: %zu\n", ft_strlcat(dst, src, size));
	printf("%s\n", dst);

	printf("BSD ft_strlcat: %zu\n", strlcat(dst1, src, size));
	printf("%s\n", dst1);
	
	return (0);
}*/
