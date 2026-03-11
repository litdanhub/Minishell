/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:17:22 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/11 18:30:02 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../utils/utils.h"
#include "../builtins/builtins.h"

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


static char	*ft_append_char(char *word, char c) //append each char
{
	char	*new_word;
	int		i;
	int		len;
	
	new_word = NULL;
	if (!word)
	{
		new_word = malloc (sizeof(char) * (1 + 1));
		if (!new_word)
			return (perror("minishell: malloc"), NULL);
		new_word[0] = c;
		new_word[1] = '\0';
		return (new_word);
	}
	len = ft_strlen(word);
	new_word = malloc (sizeof(char) * (len + 1 + 1));
	if (!new_word)
		return (free(word), perror("minishell: malloc"), NULL);
	i = -1;
	while (++i < len)
		new_word[i] = word[i];
	new_word[i] = c;
	new_word[i + 1] = '\0';
	free(word);
	return (new_word);
}

static char	*ft_append_word(char *word, char *str)
{
	char	*temp;
	
	if (!word)
		word = str;
	else
	{	
		temp = ft_strjoin(word, str);
		free(word);
		free(str);
		if (!temp)
			return (perror("minishell: malloc"), NULL);
		word = temp;
	}
	return (word);
}

int	ft_token_word(t_data *data, char **cursor)
{
	int		i;
	char	*word;
	char	*temp;
	t_token	*new_token;
	int		quotes;
	t_env	*env;
	char	*key;

	i = 0;
	quotes = Q_NONE;
	word = NULL;
	temp = NULL;
	key = NULL;
	while ((*cursor)[i])
	{
		if (ft_quotes((*cursor)[i], &quotes))
		{	
			i++;
			continue ;
		}
		if (quotes != Q_SINGLE && (*cursor)[i] =='$') //expansion
		{
			if ((*cursor)[i + 1] == '?') //$?
			{
				temp = ft_itoa(data->exit_code);
				if (!temp)
					return (perror("minishell: malloc"), free(word), 1);
				word = ft_append_word(word, temp);
				if (!word)
					return (1);
				i += 2;
				continue ;
			}
			else if ((*cursor)[i + 1] == '$') //$$
			{
				temp = ft_strdup("$$");
				if (!temp)
					return (perror("minishell: malloc"), free(word), 1);
				word = ft_append_word(word, temp);
				if (!word)
					return (1);
				i += 2;
				continue ;

			}
			else if (ft_isalpha((*cursor)[i + 1]) || (*cursor)[i + 1] == '_') //var expansion
			{
				i++;
				while ((*cursor)[i] && (ft_isalpha((*cursor)[i]) || ft_isdigit((*cursor)[i]) || (*cursor)[i] == '_'))
				{
					key = ft_append_char(key, (*cursor)[i]);
					if (!key)
						return (1);
					i++;
				}
				env = ft_env_search_key(data, key);
				free(key);
				key = NULL;
				if (env) //value is found
				{
					temp = ft_strdup(env->value);
					if (!temp)
						return (perror("minishell: malloc"), free(word), 1);
					word = ft_append_word(word, temp);
					if (!word)
						return (1);
				}
				continue ;
			}
		}
		if (ft_special_char((*cursor)[i]) && quotes == Q_NONE)
			break ;
		if (quotes == Q_NONE && ((*cursor)[i] == '\\' || (*cursor)[i] == ';'))
			return (ft_print_error("syntax error: unsupported character"), 2);
		word = ft_append_char(word, (*cursor)[i]);
		if (!word)
			return (1);
		i++;
	}

	
	if (quotes == Q_SINGLE || quotes == Q_DOUBLE)
		return (free(word), ft_print_error("syntax error: unclosed quotes"), 2);
	if (!word)
	{
		word = ft_strdup(""); //or *cursor += i; return (0); instead of empty line
		if (!word)
			return (perror("minishell: malloc"), 1);
	}
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
	int		exit_status;
	
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
			exit_status = ft_token_word(data, &cursor);
			if (exit_status) //1 malloc err, 2 syntax err
				return (exit_status);
		}
	}
	return (0);
}
