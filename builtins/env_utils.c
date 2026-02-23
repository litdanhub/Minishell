/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:41:16 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/23 17:01:45 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*ft_env_search_key(t_data *data, char *search) //searches for KEY in env and returns VALUE
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (tmp->key && search && ft_strncmp(tmp->key, search,
				ft_strlen(search)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
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

int	ft_env_update_value()
{

	return (0);
}
