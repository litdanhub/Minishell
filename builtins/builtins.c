/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 13:25:58 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/22 19:20:04 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*ft_pwd(void)
{
	char	path_buffer[PATH_MAX];
	char	*cwd;

	if (!getcwd(path_buffer, PATH_MAX))
	{
		perror("minishell: pwd");
		return (NULL);
	}
	cwd = ft_strdup(path_buffer);
	if (!cwd)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	return (cwd);
}

void	ft_env(t_data *data)
{
	t_env *tmp;


   if (!data || !data->env)
       return ;
   tmp = data->env;
   while (tmp)
   {
       printf("%s=%s\n", tmp->key, tmp->value);
       tmp = tmp->next;
   }
}
