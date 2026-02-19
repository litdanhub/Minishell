/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:17:22 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/19 17:41:11 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_tokens(t_data *data) //delete after use
{
	t_token	*tmp;

	if (!data || !data->tokens)
		return ;
	tmp = data->tokens;
	while (tmp)
	{
		printf("type %d value %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

int	ft_special_char(char c) //maybe add quotes here?
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

void	ft_add_node(t_token **tokens, t_token *new_node)
{
	t_token	*temp;

	if (!new_node) //dont need as i check !new_token after I malloced it //but maybe if other functions dont check for NULL before passing?
		return ;
	if (!*tokens) // If no tokens yet
	{
		*tokens = new_node;
		return ;
	}
	temp = *tokens; //if we loop through *tokens, we will lose the pointer
	while (temp->next) //while temp->next != NULL, looping to find token->next == NULL
		temp = temp->next;
	temp->next = new_node; //each new_node has already NULL in theirs ->next, so no need to add NULL
}

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (printf("minishell: malloc has failed\n"), NULL);
	new->value = value;
	new->type = type;
	new->quote = Q_NONE; //Default value
	new->next = NULL;
	return (new);
}

int	ft_token_word(t_data *data, char **cursor)
{
	int		i;
	char	*word;
	t_token	*new_token;

	i = 0;
	while ((*cursor)[i] && !ft_special_char((*cursor)[i])) //starting, then ending the word with a special char
		i++; //the length of the word
	word = ft_substr(*cursor, 0, i);
	if (!word)
		return (printf("minishell: malloc has failed\n"), 1);
	new_token = ft_new_token(word, T_WORD);
	if (!new_token)
	{
		free(word);
		return (1);
	}
	ft_add_node(&data->tokens, new_token);
	*cursor += i;
	return (0);
}

static int	ft_token_redir_help(t_data *data, char *word, t_token_type type)
{
	t_token			*new_token;

	if (!word)
		return (printf("minishell: malloc has failed\n"), 1);
	new_token = ft_new_token(word, type);
	if (!new_token)
	{
		free(word);
		return (1);
	}
	ft_add_node(&data->tokens, new_token);
	return (0);
}

int	ft_token_redir_in(t_data *data, char **cursor)
{
	int				i;
	char			*word;
	t_token_type	type;

	i = 0;
	word = NULL;
	if ((*cursor)[i] == '<' && (*cursor)[i + 1] == '<')
	{
		word = ft_strdup("<<");
		i = 2;
		type = T_HEREDOC;
	}
	else
	{
		word = ft_strdup("<");
		i = 1;
		type = T_REDIR_IN;
	}
	if (ft_token_redir_help(data, word, type))
		return (1);
	*cursor += i;
	return (0);
}

int	ft_token_redir_out(t_data *data, char **cursor)
{
	int				i;
	char			*word;
	t_token_type	type;

	i = 0;
	word = NULL;
	if ((*cursor)[i] == '>' && (*cursor)[i + 1] == '>')
	{
		word = ft_strdup(">>");
		i = 2;
		type = T_REDIR_APPEND;
	}
	else
	{
		word = ft_strdup(">");
		i = 1;
		type = T_REDIR_OUT;
	}
	if (ft_token_redir_help(data, word, type))
		return (1);
	*cursor += i;
	return (0);
}

int	ft_token_pipe(t_data *data, char **cursor)
{
	int		i;
	char	*word;
	t_token	*new_token;

	i = 0;
	word = ft_strdup("|");
	if (!word)
		return (printf("minishell: malloc has failed\n"), 1);
	i++;
	new_token = ft_new_token(word, T_PIPE);
	if (!new_token)
	{
		free(word);
		return (1);
	}
	ft_add_node(&data->tokens, new_token);
	*cursor += i;
	return (0);
}

int	ft_lexing(t_data *data)
{
	char	*cursor;

	cursor = data->prompt;
	while (*cursor)
	{
		while (*cursor && ft_isspace(*cursor)) //skip white space
			cursor++;
		if (!*cursor)
			break ;
		if (*cursor == '|')
		{
			if (ft_token_pipe(data, &cursor)) //start a pipe token
				return (1);
		}
		else if (*cursor == '<')
		{
			if (ft_token_redir_in(data, &cursor)) //start a redirect IN or HEREDOC token
				return (1);
		}
		else if (*cursor == '>')
		{
			if (ft_token_redir_out(data, &cursor)) //start a redirect OUT or APPEND token
				return (1);
		}
		//add quotes here
		else
		{
			if (ft_token_word(data, &cursor)) //start a word token, sending an address of a right cursor of propmt
				return (1);
		}
	}
	return (0);
}

int	ft_proccess_prompt(t_data *data)
{
	if (ft_lexing(data))
	{
		return (1);
	}
	ft_print_tokens(data); //delete
	return (0);
}
