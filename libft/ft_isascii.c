/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:42:40 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 11:58:31 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char *str = "12ab!öäüß34*cd#";
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isascii(str[i]) == 1)
			printf("%c is ascii char\n", str[i]);
		else
			printf("%c is non-ascii char\n", str[i]);
		i++;
	}
	return (0);
}*/