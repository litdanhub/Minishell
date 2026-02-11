/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:28:31 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 11:58:12 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char *str = "12ab! 34*cd#";
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1)
			printf("%c is alphanumeric\n", str[i]);
		else
			printf("%c is non-alphanumeric\n", str[i]);
		i++;
	}
	return (0);
}*/