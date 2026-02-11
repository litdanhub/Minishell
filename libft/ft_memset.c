/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:53:44 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/15 15:37:01 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	if (!s)
		return (NULL);
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char s[] = "Hello there world!";
	char c = '#';
	size_t n = 5;
	ft_memset(s+6, c, n);
	printf("My ft_memset: %s\n", s);
	
	char s1[] = "Hello there world!";
	
	memset(s1+6, c, n);
	printf("Libc memset : %s\n", s1);

	/////////////////////////////////

	int s[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int c = 0;
	size_t n = 3;
	ft_memset(s+4, c, sizeof(int) * n);
	size_t i = 0;
	printf("My ft_memset: ");
	while (i < 10)
	{
		printf("%d ", s[i]);
		i++;
	}
	
	int s1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	memset(s1+4, c, sizeof(int) * n);
	i = 0;
	printf("\nLibc memset:  ");
	while (i < 10)
	{
		printf("%d ", s1[i]);
		i++;
	}
	printf("\n");
	return (0);
}*/