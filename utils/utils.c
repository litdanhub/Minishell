/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:20:11 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/19 16:08:32 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free(t_data *data) //free allocated memory from readline and tokens
{
	t_token *current;
	t_token *next_node;

	if (!data)
		return;
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

void	ft_init(char **envp, t_data *data)
{
	(void) envp;//add parsing envp
	
	//add more vars to initialize
	data->prompt = NULL;
	data->env = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	data->last_status = 0;
}
