/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:52:23 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/26 18:12:01 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_free_env(t_data *data)
{
	t_env	*current;
	t_env	*next_node;

	if (!data || !data->env)
		return ;
	current = data->env;
	while (current)
	{
		next_node = current->next;
		if (current->key)
			free(current->key); //free malloced key
		if (current->value)
			free(current->value); //free malloced value
		free(current); //free the struct node itself
		current = next_node; //go to next node
	}
	data->env = NULL;	
}

void	ft_free_tokens(t_data *data)
{
	t_token	*current;
	t_token	*next_node;

	if (!data || !data->tokens)
		return ;
	current = data->tokens;
	while (current)
	{
		next_node = current->next;
		if (current->value)
			free(current->value); //free value allocation
		free(current); //free the struct node itself
		current = next_node; //go to next node
	}
	data->tokens = NULL;
}

void	ft_free_prompt(t_data *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

void	ft_free_cmds(t_data *data)
{
	t_cmd	*current;
	t_cmd	*next_node;
	int		i;

	if (!data || !data->cmds)
		return ;
	current = data->cmds;
	while (current)
	{
		next_node = current->next;
		i = 0;
		while (current->argv && current->argv[i])
		{
			if (current->argv[i])
				free(current->argv[i]); //free value allocation
			i++;
		}
		if (current->redirs) //free redirs, value is freed in ft_free_tokens
			free(current->redirs);
		free(current->argv); //free *argv
		free(current); //free the struct node itself
		current = next_node; //go to next node
	}
	data->cmds = NULL;
}

