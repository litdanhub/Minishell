/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:39:47 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/26 12:34:10 by dsalimov         ###   ########.fr       */
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
		cmd = cmd->next;
	}
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

int	ft_parsing(t_data *data)
{
	t_token	*token;
	t_cmd	*new_cmd;
	t_cmd	*cmd;
	char	**argv;
	int		i;
	
	token = data->tokens;
	while (token) //count PIPES and allocate mem for argv[i]
	{
		i = 0;
		argv = NULL;
		while (token && token->type != T_PIPE)
		{	
			if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
				|| token->type == T_REDIR_APPEND || token->type == T_HEREDOC)
					i--; //decrement the following WORD (file), it will be in t_redir
			if (token->type == T_WORD) //add skipping redir here
				i++;
			token = token->next;
		}
		printf("%d\n", i); //delete
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
				token = token->next;		
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
