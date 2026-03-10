/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:17:22 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/10 11:47:57 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../utils/utils.h"

void	ft_print_tokens(t_data *data) //delete after use
{
	t_token	*tmp;

	if (!data || !data->tokens)
		return ;
	tmp = data->tokens;
	printf("---------LEXING---------\n");
	while (tmp)
	{
		printf("type %d value %s            quotes %d\n", tmp->type, tmp->value, tmp->quote);
		tmp = tmp->next;
	}
}


int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

void	ft_add_token_node(t_token **tokens, t_token *new_node)
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

t_token	*ft_new_token(char *value, t_token_type type, int quotes)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (perror("minishell: malloc"), NULL);
	new->value = value;
	new->type = type;
	if (quotes)
		new->quote = quotes;
	else
		new->quote = Q_NONE;
	new->next = NULL;
	return (new);
}

static int	ft_token_redir_help(t_data *data, char *word, t_token_type type)
{
	t_token			*new_token;

	if (!word)
		return (perror("minishell: malloc"), 1);
	new_token = ft_new_token(word, type, 0);
	if (!new_token)
	{
		free(word);
		return (1);
	}
	ft_add_token_node(&data->tokens, new_token);
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
		return (perror("minishell: malloc"), 1);
	i++;
	new_token = ft_new_token(word, T_PIPE, 0);
	if (!new_token)
	{
		free(word);
		return (1);
	}
	ft_add_token_node(&data->tokens, new_token);
	*cursor += i;
	return (0);
}

static char	*ft_concan(char *str, char c) //concatenating each char
{
	char	*new_str;
	int		i;
	int		len;
	
	new_str = NULL;
	if (!str)
	{
		new_str = malloc (sizeof(char) * (1 + 1));
		if (!new_str)
			return (perror("minishell: malloc"), NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = malloc (sizeof(char) * (len + 1 + 1));
	if (!new_str)
		return (perror("minishell: malloc"), NULL);
	i = -1;
	while (++i < len)
		new_str[i] = str[i];
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
}

int	ft_special_char(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_quotes(char c, int *quotes)
{
	if (c == '\'' && *quotes == Q_NONE)
	{	
		*quotes = Q_SINGLE;	
		return (1);
	}
	else if (c == '"' && *quotes == Q_NONE)
	{	
		*quotes = Q_DOUBLE;	
		return (1);
	}
	else if ((c == '\'' && *quotes == Q_SINGLE) || (c == '"' && *quotes == Q_DOUBLE))
	{	
		*quotes = Q_NONE;	
		return (1);
	}
	return (0);
}
//echo "Hello $USER" 'and $USER'

int	ft_token_word(t_data *data, char **cursor)
{
	int		i;
	char	*word;
	char	*temp;
	t_token	*new_token;
	int		quotes;
	char	*exit_code;

	i = 0;
	quotes = Q_NONE;
	word = NULL;
	temp = NULL;
	exit_code = NULL;
	while ((*cursor)[i])
	{
		if (ft_quotes((*cursor)[i], &quotes))
		{	
			i++;
			continue ;
		}
		if (quotes != Q_SINGLE && (*cursor)[i] =='$') //if Q_NONE or Q_DOUBLE
		{
			if ((*cursor)[++i] =='?')
			{
				exit_code = ft_itoa(data->exit_code);
				printf("STATUS AT READING %d\n", data->exit_code); //delete

				if (!exit_code)
					return (free(word), 1);
				if (!word)
					word = exit_code;
				else
				{	temp = ft_strjoin(word, exit_code);
					free(word);
					free(exit_code);
					if (!temp)
						return (perror("minishell: malloc"), 1);
				}
			}
			i++;
			continue ;
		}
		
		if (ft_special_char((*cursor)[i]) && quotes == Q_NONE)
			break ;
		if (quotes == Q_NONE && ((*cursor)[i] == '\\' || (*cursor)[i] == ';'))
			return (ft_print_error("syntax error: unsupported character"), 2); change exit stat here
		temp = ft_concan(word, (*cursor)[i]);
		free(word);
		if (!temp)
			return (1);
		word = temp;
		i++;
	}
	if (quotes == Q_SINGLE || quotes == Q_DOUBLE)
		return (free(word), ft_print_error("syntax error: unclosed quotes"), 2);
	new_token = ft_new_token(word, T_WORD, quotes);
	if (!new_token)
		return (free(word), 1);
	ft_add_token_node(&data->tokens, new_token);
	
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
		else
		{
			data->last_status = ft_token_word(data, &cursor); dont change exit stat here
			printf("STATUS after exec ft_token_word %d\n", data->last_status);
			if (data->last_status) //1 malloc err, 2 syntax err
				return (data->last_status);
		}
	}
	return (0);
}
