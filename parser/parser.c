/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:39:47 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/26 18:05:50 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_print_cmd(t_data *data) //delete after use
{
	t_cmd	*cmd;
	int		i;

	cmd = data->cmds;
	while (cmd)
	{
		i = 0;
		
		while (cmd->argv[i])
		{
			printf("\"%s\", ", cmd->argv[i]);
			i++;
		}
		printf("\"%s\"", cmd->argv[i]); //for null
		printf("\n");
		if (cmd->redirs)
		{
			printf("Type %d Target ", cmd->redirs->type);
			printf("%s\n\n", cmd->redirs->target);
		}
		cmd = cmd->next;
	}
}

t_redir	*ft_new_redir(char *value, t_token_type type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (perror("minishell: malloc"), NULL);
	new->type = type;
	new->target = value;
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


int	ft_parsing(t_data *data) //the rule is always < > << >> and file
{
	t_token			*token;
	t_cmd			*new_cmd;
	t_cmd			*cmd;
	t_redir			*new_redir;
	t_token_type	temp_type;
	char			**argv;
	int				i;
	
	token = data->tokens;
	while (token) //count PIPES and allocate mem for argv[i]
	{
		i = 0;
		argv = NULL;
		while (token && token->type != T_PIPE)
		{	
			if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
				|| token->type == T_REDIR_APPEND || token->type == T_HEREDOC)
					i--; //decrement the following WORD (file), it will be in redir
			if (token->type == T_WORD)
				i++;
			token = token->next;
		}
		argv = malloc (sizeof(char *) * (i + 1)); //allocate *argv for i words
		if (!argv)
			return (1);
		while (i >= 0) //initializing argv[i] with NULL
		{
			argv[i] = NULL;
			i--;
		}
		new_cmd = ft_new_cmd(argv);
		if (!new_cmd)
			return (free(argv), 1);
		ft_add_cmd_node(&data->cmds, new_cmd);
		if (token && token->type == T_PIPE)
			token = token->next; //since we are at PIPE, go the next token
	}
	token = data->tokens;
	cmd = data->cmds;
	while (token) //allocate each WORD in argv[i]
	{
		i = 0;
		while (token && token->type != T_PIPE)
		{	
			if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
				|| token->type == T_REDIR_APPEND || token->type == T_HEREDOC)
			{
				temp_type = token->type;
				token = token->next; //skip to WORD, and it will be skiped again in the end of the loop	
				new_redir = ft_new_redir(token->value, temp_type);
				if (!new_redir)
					return (1);
				ft_add_redir_node(&cmd->redirs, new_redir);
			}
			
			else if (token->type == T_WORD)
			{
				cmd->argv[i] = ft_strdup(token->value);
				if (!cmd->argv[i])
					return (1);
				i++;
			}
			token = token->next;
		}
		cmd->argv[i] = NULL;
		if (token && token->type == T_PIPE)
			token = token->next; //since we are at PIPE, go the next token	
		cmd = cmd->next;
	}
	ft_print_cmd(data); //delete
	return (0);
}
