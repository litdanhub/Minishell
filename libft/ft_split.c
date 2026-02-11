/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:46:34 by dsalimov          #+#    #+#             */
/*   Updated: 2025/05/19 12:20:03 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_count_words(char const *s, char c)
{
	char	**str;
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			count++;
		}
	}
	str = malloc (sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	return (str);
}

static char	**ft_array2(char **str, char *begin, char *end, size_t count)
{
	size_t	len;

	len = end - begin;
	str[count] = malloc (sizeof(char) * (len + 1));
	if (!str[count])
	{
		while (count > 0)
		{
			count--;
			free(str[count]);
		}
		free(str);
		return (NULL);
	}
	ft_memmove(str[count], begin, len);
	str[count][len] = '\0';
	return (str);
}

static char	**ft_array1(char const *s, char c, char **str)
{
	size_t	i;
	size_t	count;
	char	*begin;
	char	*end;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			begin = (char *) &s[i];
			while (s[i] && s[i] != c)
				i++;
			end = (char *) &s[i];
			if (ft_array2(str, begin, end, count) == NULL)
				return (NULL);
			count++;
		}
	}
	str[count] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = ft_count_words(s, c);
	if (str == NULL)
		return (NULL);
	str = ft_array1(s, c, str);
	if (!str)
		return (NULL);
	return (str);
}
/*
int	main(void)
{
	char	*s = ",,,Jan,Mar,,,Apr,May,,,June,,,";
	//char 	*s = NULL;
	//char	*s = "Double  space";
	//char	*s = "";
	//char	*s = "   leading space";
	//char	*s = "trailing space   ";
	//char	*s = "no_delimiters";
	
	char	c =',';
	//char	c =' ';

	char 	**str;
	int		i = 0;
	
	str = ft_split(s, c);
	if (!str)
		return (1);
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);	
		i++;
	}
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	
	return (0);
}*/