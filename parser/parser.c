/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:39:47 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/24 17:26:11 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_add_cmd_node(t_cmd **cmd, t_cmd *new_node)
{
	t_cmd	*temp;

	if (!new_node) //dont need as i check !new_token after I malloced it //but maybe if other functions dont check for NULL before passing?
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
	char	**argv;
	int		i;
	int		j;

	token = data->tokens;
	while (token)
	{
		i = 0;
		argv = NULL;
		while (token && token->type != T_PIPE)
		{	
			if (token->type == T_WORD)
				i++;
			token = token->next;
		}
		argv = malloc (sizeof(char *) * (i + 1)); //protect

		if (token && token->type == T_PIPE)
		{
			new_cmd = ft_new_cmd(argv);
			if (!new_cmd)
			{
				free(argv);
				return (1);
			}
			ft_add_cmd_node(&data->cmds, new_cmd);
			
			printf("%d\n", i);
			token = token->next;
		}
	}
	printf("%d\n", i);

	
	
	return (0);
}
