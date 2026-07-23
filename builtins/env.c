/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:58:36 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/19 21:16:05 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_key_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

int	ft_parse_env(char *envp, char **key, char **value)
{
	char	*tmp;
	int		eql_char;

	*key = NULL;
	*value = NULL;
	eql_char = 0;
	tmp = ft_strchr(envp, '=');
	if (!tmp) // no "="
	{
		*key = ft_strdup(envp); // key = the whole line
		if (!*key)
			return (perror("minishell: malloc"), 1);
	}
	else
	{
		eql_char = tmp - envp;
		*key = ft_substr(envp, 0, eql_char);
		*value = ft_substr(envp, eql_char + 1, ft_strlen(envp) - eql_char - 1);
		if (!*key || !*value)
		{
			ft_free_key_value(*key, *value);
			return (perror("minishell: malloc"), 1);
		}
	}
	return (0);
}

int	ft_update_env_shlvl(t_data *data)
{
	t_env	*node;
	char	*new_shlvl;
	
	node = ft_env_search_key(data, "SHLVL");
	if (node) //node has SHLVL, need to increament it
	{
		if (ft_atoi(node->value) <= 0) //if shlvl negative, 0 or character
			new_shlvl = ft_strdup("1");
		else
			new_shlvl = ft_itoa(ft_atoi(node->value) + 1);
		if (!new_shlvl)
			return (perror("minishell: malloc"), 1);
		free(node->value);
		node->value = new_shlvl;
	}
	else //no SHLVL, add a new node
	{
		if (ft_add_env_shlvl(data))
			return (1);
	}
	return (0);
}

int	ft_init_envp(t_data *data, char **envp, char *argv)
{
	int		i;
	char	*value;
	char	*key;
	t_env	*new_env;

	i = -1;
	if (!envp || !envp[0]) //if env -i ./minishell, add PWD, SHLVL and _
		return (ft_no_env(data, argv));
	else
	{
		while (envp[++i])
		{
			if (ft_parse_env(envp[i], &key, &value))
				return (1);
			new_env = ft_new_env(key, value);
			if (!new_env)
				return (ft_free_key_value(key, value), 1);
			ft_add_env_node(&data->env, new_env);
		}
		if (ft_update_env_shlvl(data)) //increament SHLVL +1, if missing or invalid then 1
			return (1);
	}
	return (0);
}
