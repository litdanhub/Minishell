/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:47:30 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/16 16:57:39 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*ft_new_redir(char *value, t_token_type type, int quotes)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (perror("minishell: malloc"), NULL);
	new->type = type;
	new->target = value;
	new->quoted = quotes; //if 0 don't expand in heredoc
	new->next = NULL;
	return (new);
}

void	ft_add_redir_node(t_redir **redir, t_redir *new_node)
{
	t_redir	*temp;

	if (!new_node) //dont need as i check !new_cmd after I malloced it //but maybe if other functions dont check for NULL before passing?
		return ;
	if (!*redir) // If no redir yet
	{
		*redir = new_node;
		return ;
	}
	temp = *redir; //if we loop through *redir, we will lose the pointer
	while (temp->next) //while temp->next != NULL, looping to find redir->next == NULL
		temp = temp->next;
	temp->next = new_node; //each new_node has already NULL in theirs ->next, so no need to add NULL
}

t_cmd	*ft_new_cmd(char **argv)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (perror("minishell: malloc"), NULL);
	new->argv = argv;
	new->path = NULL;
	new->redirs = NULL;
	new->infile = 0;
	new->outfile = 1;
	new->next = NULL;
	return (new);
}

void	ft_add_cmd_node(t_cmd **cmd, t_cmd *new_node)
{
	t_cmd	*temp;

	if (!new_node) //dont need as i check !new_cmd after I malloced it //but maybe if other functions dont check for NULL before passing?
		return ;
	if (!*cmd) // If no cmds yet
	{
		*cmd = new_node;
		return ;
	}
	temp = *cmd; //if we loop through *cmds, we will lose the pointer
	while (temp->next) //while temp->next != NULL, looping to find cmd->next == NULL
		temp = temp->next;
	temp->next = new_node; //each new_node has already NULL in theirs ->next, so no need to add NULL
}
