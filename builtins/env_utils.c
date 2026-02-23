/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 16:41:16 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/23 19:47:08 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*ft_env_search_key(t_data *data, char *search) //searches for KEY in env and returns *node
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		if (node->key && search &&
			ft_strncmp(node->key, search, ft_strlen(search)) == 0 &&
			ft_strlen(search) == ft_strlen(node->key))
			return (node);
		node = node->next;
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
