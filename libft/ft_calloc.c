/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:34:59 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/15 12:09:43 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*cal;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	cal = (void *) malloc (nmemb * size);
	if (!cal)
		return (NULL);
	ft_bzero(cal, nmemb * size);
	return (cal);
}
/*
int	main(void)
{	
	size_t nmemb = 5;
	size_t	size = 5;
	void *cal;
	unsigned char *arr;
	size_t i;
	
	cal = ft_calloc (nmemb, size);
	arr = (unsigned char *) cal;
	i = 0;
	printf("My ft_calloc: ");
	while (i < nmemb)
	{
		printf("%d", arr[i]);
		i++;
	}
	printf("\n");	
	free (cal);
	
		
	cal = calloc (nmemb, size);
	arr = (unsigned char *) cal;
	i = 0;
	printf("Libc calloc:  ");
	while (i < nmemb)
	{
		printf("%d", arr[i]);
		i++;
	}
	free (cal);
	printf("\n");	

	return (0);
}*/