/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:56:57 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/16 11:46:47 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_move_backward(unsigned char *d, unsigned char *s, size_t i)
{
	while (i > 0)
	{
		i--;
		d[i] = s[i];
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dest || !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (d > s)
	{
		i = n;
		ft_move_backward(d, s, i);
	}
	return (dest);
}
/*
int	main(void)
{
	char dest[] = "ABCDEFGHIJK";
	char *src = "12345";
	char dest1[] = "ABCDEFGHIJK";
	char *src1 = "12345";
	size_t n = 5;
	ft_memmove(dest+2, src, n);
	memmove(dest1+2, src1, n);
	printf("My ft_memmove: %s\n", dest);
	
	printf("Libc memmove:  %s\n", dest1);

///////////////////////////////////////////
	int dest[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int src[5] = {15, 16, 17, 18, 19};

	int dest1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int src1[5] = {15, 16, 17, 18, 19};
	size_t n = 5;

	printf("My ft_memmove: ");
	ft_memmove(dest+3, dest, sizeof(int) * n);
	size_t i = 0;
	while (i < 10)
	{
		printf("%d ", dest[i]);
		i++;
	}
	
	printf("\nLibc memmove:  ");
	memmove(dest1+3, dest1, sizeof(int) * n);
	i = 0;
	while (i < 10)
	{
		printf("%d ", dest1[i]);
		i++;
	}
	return (0);
}*/