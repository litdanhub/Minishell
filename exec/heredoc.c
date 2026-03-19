/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:09:30 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/19 16:33:48 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_loop_readline(t_data *data, char *delim)
{
	(void) data;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line) //ctrl+D
		{	
			//ft_cleanup_exit(&data);
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0 )
		{	
			free(line);
			break ;
		}
		free(line);
		//ft_process_prompt(&data);
		
	}

	return (0);
}

char	*ft_heredoc(t_data *data)
{
	t_cmd	*cmd_node;
	t_redir	*redir_node;

	cmd_node = data->cmds;
	while (cmd_node)
	{
		redir_node = cmd_node->redirs;
		while (redir_node)
		{
			if (redir_node->type == T_HEREDOC)
			{	
				ft_loop_readline(data, redir_node->target);
			}
			redir_node = redir_node->next;
		}
		cmd_node = cmd_node->next;
	}
	return (NULL);
}
