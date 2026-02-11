/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:52:24 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 12:53:45 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long nb)
{
	int	count;

	count = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static char	*ft_array(int sign, char *str, int count, long nb)
{
	if (sign == 1)
	{
		str[0] = '-';
		str[count + sign] = '\0';
	}
	else
		str[count] = '\0';
	while (count > 0)
	{
		str[count + sign - 1] = (nb % 10) + '0';
		nb = nb / 10;
		count--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;
	int		sign;
	long	nb;

	nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	sign = 0;
	if (nb < 0)
	{
		nb = -nb;
		sign = 1;
	}
	count = ft_count(nb);
	str = malloc (sizeof(char) * (count + sign + 1));
	if (!str)
		return (NULL);
	str = ft_array(sign, str, count, nb);
	return (str);
}
/*
int	main(void)
{
	int			n = -123456;
	//int		n = 0;
	//int		n = -1000;
	//int		n = INT_MAX;
	//int		n = INT_MIN;

	char	*str;
	str = ft_itoa(n);
	printf("%s\n", str);
	free(str);

	return (0);
}*/