/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:20:11 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/20 13:36:19 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(t_data *data)
{
	//add more vars to initialize
	data->prompt = NULL;
	data->env = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	data->last_status = 0;
}

void	ft_print_error(char *msg)
{
	write(2, "minishell: ", 11);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	ft_free(t_data *data) //free allocated memory from readline and tokens
{
	t_token	*current;
	t_token	*next_node;

	if (!data)
		return ;
	current = data->tokens;
	while (current)
	{
		next_node = current->next;
		if (current->value)
			free(current->value); //free value (lile "word") allocation
		free(current); //free the struct node itself
		current = next_node; //go to next node
	}
	data->tokens = NULL;
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("malloc"), NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
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

int	ft_init_envp(t_data *data, char **envp)
{
	int		i;
	int		equal_char;
	char	*value;
	char	*tmp;
	char	*key;
	t_env	*new_env;
		
	i = 0;
	equal_char = 0;
	if (!envp || !envp[0]) //was run env -i ./minishell
	{
		//need just PWD, SHLVL=1 and _
		//PWD: getcwd() to get the current working directory
		//SHLVL: SHLVL should be 1
		//_ (underscore): absolute path of the running shell
	}
	else //parse and increament SHLVL +1, if missing or invalid then 1
	{
		while (envp[i])
		{
			key = NULL;
			value = NULL;
			tmp = ft_strchr(envp[i], '=');
			if (!tmp) //no "="
			{
				key = ft_strdup(envp[i]); //key = the whole line
				if (!key)
					return (perror("malloc"), 1);
				value = NULL; //value = NULL
			}
			else
			{
				equal_char = tmp - envp[i];
				key = ft_substr(envp[i], 0, equal_char);
				value = ft_substr(envp[i], equal_char + 1, ft_strlen(envp[i]) - equal_char - 1);
				if (!key || !value)
				{
					if (key)
						free (key);
					if (value)
						free (value);
					return (perror("malloc"), 1);
				}
			}
			new_env = ft_new_env(key, value);
			if (!new_env)
			{ 
				if (key)
					free (key);
				if (value)
					free (value);
				return (1);
			}
			ft_add_env_node(&data->env, new_env);
			i++;
		}
		t_env	*temp; //delete
		temp = data->env;
		while (temp)
		{
			printf("%s | %s\n", temp->key, temp->value);
			temp = temp->next;
		}
	}
	return (0);
}
