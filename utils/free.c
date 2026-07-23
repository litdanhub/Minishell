/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:52:23 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/19 21:16:46 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	ft_free_redirs(t_cmd *current)
{
	t_redir	*next_redir;

	while (current->redirs)
	{
		next_redir = current->redirs->next;
		free(current->redirs);
		current->redirs = next_redir;
	}
}

void	ft_free_cmds(t_data *data)
{
	t_cmd	*current;
	t_cmd	*next_cmd;
	int		i;

	if (!data || !data->cmds)
		return ;
	current = data->cmds;
	while (current)
	{
		next_cmd = current->next;
		i = 0;
		while (current->argv && current->argv[i])
		{
			if (current->argv[i])
				free(current->argv[i]); //free value allocation
			i++;
		}
		if (current->path)
			free(current->path);
		ft_free_redirs(current);
		free(current->argv); //free *argv
		free(current); //free the struct node itself
		current = next_cmd; //go to next node
	}
	data->cmds = NULL;
}
