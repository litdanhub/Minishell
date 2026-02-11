/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:13:21 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 11:56:16 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	if (!s)
		return ;
	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	int i = 0;
	
	int s[10] = {1,2,3,4,5,6,7,8,9,10};
	size_t n = 5;
	ft_bzero(s, sizeof(int) * n);
	printf("My ft_bzero :");
	while (i < 10)
	{
		printf("%d", s[i]);
		i++;
	}
	
	i = 0;
	int s1[10] = {1,2,3,4,5,6,7,8,9,10};
	bzero(s1, sizeof(int) * n);
	printf("\nLibc bzero  :");
	while (i < 10)
	{
		printf("%d", s1[i]);
		i++;
	}
	////////////////////////////////////////
	
	char s[12] = "Hello world";
	size_t n = 6;
	
	printf("My ft_bzero :\n");
	ft_bzero(s, sizeof(char) * n);
	while (i < 12)
	{
		write(1, &s[i], 1);
		i++;
	}
	
	i = 0;
	char s1[12] = "Hello world";
	
	printf("\nLibc bzero  :\n");
	bzero(s1, sizeof(char) * n);
	while (i < 12)
	{
		write(1, &s1[i], 1);
		i++;
	}
	return (0);
}*/