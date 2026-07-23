/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:09:30 by dsalimov          #+#    #+#             */
/*   Updated: 2026/04/17 15:37:54 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_readline(char *line, char *word)
{
	if (line)
		free(line);
	if (word)
		free(word);
}

int	ft_loop_readline(t_data *data, char *delim, int quoted)
{
	char	*line;
	char	*word;
	int		i;
	int		result;
	char	*heredoc; //do i use this?
	char	*temp; //do i use this?
	//сделать 2 прогона:
	//line = Hello world
	//line = Hi $USER
	//line = EOF
	
	//echo $USER hihi
	//cat$USER
	
	heredoc = NULL;
	while (1)
	{
		//line = NULL;
		word = NULL;
		temp = NULL;
		line = readline("> ");
		if (!line) //ctrl+D //try it!
		{
			ft_free_readline(line, word);
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0 ) //found delim
		{
			free(line); //here word?????
			break ;
		}
		if (quoted == Q_NONE) //expand VAR if not quoted
		{
			i = 0;
			while(line[i])
			{
				result = 0;
				if ((line)[i] == '$' && (line)[i + 1] != '$')
				{
					result = ft_expand(data, &line, &i, &word);	
					if (result == 1) //malloc error
						return (ft_free_readline(line, word), 1);
					else if (result == 2)
						continue ;
				}
				else
				{
					word = ft_append_char(word, line[i]);
					if (!word)
						return (ft_free_readline(line, word), 1);
				}
				i++;
			}
		}
		if (word)
		{
			printf("I have WORD\n"); //delete
			temp = ft_append_word(heredoc, word); //protect
		}
		else
		{
			printf("I have LINE\n"); //delete
			temp = ft_append_word(heredoc, line); //protect
		}
		heredoc = temp;
		//ft_free_readline(line, word);
		//printf("-->%s\n", word);

		ft_free_readline(line, word);
	}

	
	printf("%s\n", heredoc);
	free(heredoc);
	return (0);
}

int	ft_heredoc(t_data *data)
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
				if (ft_loop_readline(data, redir_node->target, redir_node->quoted))
					return (1);
			}
			redir_node = redir_node->next;
		}
		cmd_node = cmd_node->next;
	}
	return (0);
}
