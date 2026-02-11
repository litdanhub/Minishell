/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:11:07 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 12:52:35 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*str;
	char	*begin;
	char	*end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	begin = (char *) &s1[i];
	i = ft_strlen(s1);
	while (i > 0 && ft_strchr(set, s1[i]) != NULL)
		i--;
	end = (char *) &s1[i] + 1;
	len = end - begin;
	str = malloc (sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	ft_memmove(str, begin, len);
	return (str);
}
/*
int	main(void)
{
	char	*s1 = "1231Hello world3123", *set = "123";
	//char	*s1 = "", *set = "abc";               //returns: ""
	//char	*s1 = "   hello world   ", *set = ""; //returns: "   hello world   "
	//char	*s1 = "xxx   xxx", *set = " x";       //returns: ""
	//char	*s1 = "abc", *set = "abc";            //returns: ""
	//char	*s1 = "abc", *set = "xyz";            //returns: "abc"
	//char	*s1 = "   abc   ", *set = " ";        //returns: "abc"
	//char	*s1 = "xyabcxy", *set = "xy";         //returns: "abc"
	//char	*s1 = "xxabc yy", *set = "xy ";       //returns: "abc"
	//char	*s1 = "abc", *set = "cba";            //returns: ""
	//char	*s1 = "   ", *set = " ";              //returns: ""
	//char	*s1 = NULL, *set = "abc";             //returns: NULL
	//char	*s1 = "abc", *set = NULL;             //returns: NULL
	
	char	*str;
	str = ft_strtrim(s1, set);
	printf("%s\n", str);
	free (str);
	
	return (0);
}*/