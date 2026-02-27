/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:39:47 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/27 17:56:09 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_print_cmd(t_data *data) //delete after use
{
	t_cmd	*cmd;
	t_redir	*redir;
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
			redir = cmd->redirs;
			while(redir)
			{
				printf("Type %d Target %s\n", redir->type, redir->target);
				redir = redir->next;
			}
			printf("\n");
		}
		cmd = cmd->next;
	}
}

static int	ft_pars_count_pipes(t_token **token)
{
	int	i;
	
	i = 0;
	while (*token && (*token)->type != T_PIPE)
	{	
		if ((*token)->type == T_REDIR_IN || (*token)->type == T_REDIR_OUT
			|| (*token)->type == T_REDIR_APPEND || (*token)->type == T_HEREDOC)
				i--; //decrement the following WORD (file), it will be in redir
		if ((*token)->type == T_WORD)
			i++;
		*token = (*token)->next;
	}
	return (i);
}

static int	ft_first_pass(t_data *data)
{
	t_token			*token;
	t_cmd			*new_cmd;
	char			**argv;
	int				i;

	token = data->tokens;
	while (token) //count PIPES and allocate mem for argv[i]
	{
		argv = NULL;
		i = ft_pars_count_pipes(&token);
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
	return (0);
}

static int	ft_pars_alloc_argv_redir(t_token **token, int *i, t_cmd **cmd) //allocate argv[i] and redirs
{
	t_token_type	temp_type;
	t_redir			*new_redir;

	while (*token && (*token)->type != T_PIPE)
	{
		if ((*token)->type == T_REDIR_IN || (*token)->type == T_REDIR_OUT
			|| (*token)->type == T_REDIR_APPEND || (*token)->type == T_HEREDOC)
		{
			temp_type = (*token)->type;
			*token = (*token)->next; // skip to WORD, and it will be skiped again in the end of the loop
			new_redir = ft_new_redir((*token)->value, temp_type);
			if (!new_redir)
				return (1);
			ft_add_redir_node(&(*cmd)->redirs, new_redir);
		}
		else if ((*token)->type == T_WORD)
		{
			(*cmd)->argv[*i] = ft_strdup((*token)->value);
			if (!(*cmd)->argv[*i])
				return (1);
			(*i)++;
		}
		*token = (*token)->next;
	}
	return (0);
}

int	ft_parsing(t_data *data) //the rule is always < > << >> and file/EOF
{
	t_token			*token;
	int				i;
	t_cmd			*cmd;

	if (ft_first_pass(data))
		return (1);
	token = data->tokens;
	cmd = data->cmds;
	while (token) //allocate each WORD in argv[i]
	{
		i = 0;
		if (ft_pars_alloc_argv_redir(&token, &i, &cmd))
			return (1);
		cmd->argv[i] = NULL;
		if (token && token->type == T_PIPE)
			token = token->next; //since we are at PIPE, go the next token	
		cmd = cmd->next;
	}
	ft_print_cmd(data); //delete
	return (0);
}
