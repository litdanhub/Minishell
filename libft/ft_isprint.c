/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:10:48 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/21 13:10:25 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char *str = "12ab !3\n4*	cd#";
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 1)
			printf("%c is printable\n", str[i]);
		else
			printf("%c is non-printable\n", str[i]);
		i++;
	}
	return (0);
}*/