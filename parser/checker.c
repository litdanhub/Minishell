/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 18:39:33 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/02 17:51:22 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_redir_flag(t_token *token) //if token is either REDIR
{
	if ((token->type == T_REDIR_IN) || (token->type == T_REDIR_OUT)
		|| (token->type == T_REDIR_APPEND) || (token->type == T_HEREDOC))
		return (1);
	return (0);
}

static void	ft_print_syntax_err(char *msg)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, msg, ft_strlen(msg));
	write(2, "'\n", 2);
}

int	ft_check_lexing(t_data *data) //checking pipes and redirs
{
	t_token	*token;

	if (!data || !data->tokens)
		return (0);
	token = data->tokens;
	if (token->type == T_PIPE) //PIPE can't be fisrt token
		return (ft_print_syntax_err("|"), 2);
	while (token)
	{
		if (token->next && token->type == T_PIPE && token->next->type == T_PIPE) // no ||
			return (ft_print_syntax_err("|"), 2);
		if (token->next && ft_redir_flag(token) && token->next->type != T_WORD) //REDIR must be followed by WORD
			return (ft_print_syntax_err(token->next->value), 2);
		if (!token->next && token->type == T_PIPE) //PIPE can't be last token
			return (ft_print_syntax_err("newline"), 2);
		if (!token->next && ft_redir_flag(token)) //REDIR can't be last token
			return (ft_print_syntax_err("newline"), 2);
		token = token->next;
	}
	return (0);
}
