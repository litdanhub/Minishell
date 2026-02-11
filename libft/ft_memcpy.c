/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:06:36 by dsalimov          #+#    #+#             */
/*   Updated: 2025/09/17 16:27:16 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest || !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char dest[] = "Destination";
	char src[]	= "Final";
	size_t n = 5;
	printf("My ft_memcpy: %s\n", (char *) ft_memcpy(dest, src, n));
	//printf("Libc memcpy : %s\n", (char *) memcpy(dest, src, n));

//////////////////////////////////////////////////////////
	int dest[10] = {1,2,3,4,5,6,7,8,9,10};
	int src [5] = {0,0,0,0,0};
	size_t n = 5;
	
	size_t i = 0;
	printf("My ft_memcpy :"); 
	ft_memcpy(dest, src, sizeof(int) * n);
	while (i < 10)
	{
		printf("%d", dest[i]);
		i++;
	}
	printf("\n");
	i = 0;
	printf("Libc memcpy  :"); 
	memcpy(dest, src, sizeof(int) * n);
	while (i < 10)
	{
		printf("%d", dest[i]);
		i++;
	}
	printf("\n");

	return (0);
}*/