/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:15:36 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 11:24:06 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	i = 0;
	while ((us1[i] || us2[i]) && i < n)
	{
		if (us1[i] != us2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*s1 = "ABD\0a";
	char	*s2 = "ABD\0b";
	size_t	n = 3;
	
	printf("My ft_strncmp: %d\n", ft_strncmp(s1, s2, n));
	printf("Libc strncmp:  %d\n", strncmp(s1, s2, n));
	
	return (0);
}*/