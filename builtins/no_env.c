/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:12:48 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/22 22:46:55 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_add_env_pwd(t_data *data)
{
	char	*key;
	char	*value;
	t_env	*new_env;
	
	key = ft_strdup("PWD");
	if (!key)
		return (perror("minishell: malloc"), 1);
	value = ft_pwd();
	if (!value)
	{
		free(key);
		return (1);
	}
	new_env = ft_new_env(key, value);
	if (!new_env)
	{
		ft_free_key_value(key, value);
		return (1);
	}
	ft_add_env_node(&data->env, new_env);
	return (0);
}

int	ft_add_env_shlvl(t_data *data)
{
	char	*key;
	char	*value;
	t_env	*new_env;
	
	key = ft_strdup("SHLVL");
	value = ft_strdup("1");
	if (!key || !value)
	{
		ft_free_key_value(key, value);
		return (perror("minishell: malloc"), 1);
	}
	new_env = ft_new_env(key, value);
	if (!new_env)
	{
		ft_free_key_value(key, value);
		return (1);
	}
	ft_add_env_node(&data->env, new_env);
	return (0);
}

int	ft_add_env_underscore_absolute(t_data *data, char *argv)
{
	char	*key;
	char	*value;
	t_env	*new_env;
	
	key = ft_strdup("_");
	value = ft_strdup(argv);
	if (!key || !value)
	{
		ft_free_key_value(key, value);
		return (perror("minishell: malloc"), 1);
	}
	new_env = ft_new_env(key, value);
	if (!new_env)
	{
		ft_free_key_value(key, value);
		return (1);
	}
	ft_add_env_node(&data->env, new_env);
	return (0);
}

int	ft_add_env_underscore_relative(t_data *data, char *argv)
{
	char	*key;
	char	*value;
	char	*tmp;
	t_env	*new_env;
	
	key = ft_strdup("_");
	if (!key)
		return (perror("minishell: malloc"), 1);
	tmp = ft_pwd();
	if (!tmp)
		return (free(key), 1);
	value = ft_strjoin(tmp, argv + 1);
	if (!value)
	{	
		ft_free_key_value(key, tmp);
		return (perror("minishell: malloc"), 1);
	}
	free (tmp);
	new_env = ft_new_env(key, value);
	if (!new_env)
		return (ft_free_key_value(key, value) , 1);
	ft_add_env_node(&data->env, new_env);
	return (0);
}

int	ft_no_env(t_data *data, char *argv)
{
	if (ft_add_env_pwd(data))
		return (1);
	if (ft_add_env_shlvl(data))
		return (1);
	if (argv[0] == '/')
	{
		if (ft_add_env_underscore_absolute(data, argv))
			return (1);
	}
	else
	{
		if (ft_add_env_underscore_relative(data, argv))
			return (1);
	}
	return (0);
}
