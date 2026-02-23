/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:58:36 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/23 13:38:43 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_free_key_value(char *key, char *value)
{
	if (key)
		free(key);
	if (value)
		free(value);
}

void	ft_add_env_node(t_env **env, t_env *new_node)
{
	t_env	*temp;

	if (!new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("minishell: malloc"), NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
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

int	ft_init_envp(t_data *data, char **envp, char *argv)
{
	int		i;
	char	*value;
	char	*key;
	t_env	*new_env;

	i = 0;
	if (!envp || !envp[0]) //if env -i ./minishell, add PWD, SHLVL and _
	{
		if (ft_no_env(data, argv))
			return (1);
	}
	else //parse and increament SHLVL +1, if missing or invalid then 1
	{
		while (envp[i])
		{
			if (ft_parse_env(envp[i], &key, &value))
				return (1);
			new_env = ft_new_env(key, value);
			if (!new_env)
				return (ft_free_key_value(key, value), 1);
			ft_add_env_node(&data->env, new_env);
			i++;
		}
	}
	return (0);
}

/*
Case 1️⃣ SHLVL exists and is valid number
SHLVL=3

→ convert to int
→ increment by 1
→ update node value to "4"

Case 2️⃣ SHLVL exists but invalid

Examples:

SHLVL=abc
SHLVL=
SHLVL=-5

Bash behavior:

If non-numeric → reset to 1

If negative → reset to 1

If extremely large → bash resets (but you don’t need to fully replicate overflow behavior for mandatory)

So for Minishell:

👉 If invalid or negative → set to "1"

Case 3️⃣ SHLVL does NOT exist

Then you should:

👉 create new node:

key = "SHLVL"
value = "1"

and add it to env list.
*/		