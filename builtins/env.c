/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:58:36 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/23 18:01:08 by dsalimov         ###   ########.fr       */
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

int	ft_update_env_shlvl(t_data *data)
{
	char	*value;
	char	*new_shlvl;
	
		
	value = ft_env_search_key(data, "SHLVL");
	if (value) //have SHLVL need to update it
	{
		printf("Old value %s\n", value); //delete
		new_shlvl = ft_itoa(ft_atoi(value) + 1); //malloc
		if (!new_shlvl)
			return (1);
free(old_value)

node->value = ft_strdup(new_value)
		
	}
	else //no SHLVL, add a new node
	{
		printf("NO old value\n"); //delete
		if (ft_add_env_shlvl(data))
			return (1);
	}


	value = ft_env_search_key(data, "SHLVL");
	printf("New value %s\n", value);
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
	else
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
		if (ft_update_env_shlvl(data)) //increament SHLVL +1, if missing or invalid then 1
			return (1);

	}
	return (0);
}
