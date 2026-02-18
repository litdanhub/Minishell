/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:46:18 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/18 17:20:52 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*The shell inherits environment variables from its parent. We must duplicate them into our t_env list.
Increment SHLVL: We must look for the SHLVL variable. If it exists, parse it to an integer, 
increment it, and store it back. This tells the user they are in a nested shell.
Missing Env: If the shell is started with env -i./minishell (empty environment), 
we must manually create PWD, SHLVL=1, and _=/usr/bin/env to prevent crashes. */  


#include "minishell.h"

/*void ft_token_pipe(t_data *data, char **cursor)
{
    t_token *new_node;
    char    *pipe_val;

    // 1. Create the string value "|"
    pipe_val = ft_strdup("|"); 
    
    // 2. Create the Node struct
    new_node = ft_new_token(pipe_val, T_PIPE);
    
    // 3. Attach it to the train
    ft_add_token_back(&(data->tokens), new_node);
    
    // 4. Move the pointer forward past the '|'
    (*cursor)++;
}*/


//check for | and |   | -syntax error and || - not supported




int ft_special_char(char c) //maybe add quotes here?
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

/*
Every time we identify  WORD, PIPE or REDIR we:
Create the node (malloc)
Fill the node (type = T_PIPE, value = "|", etc.)
Call ft_add_token(&data->tokens, new_node) to add it
*/

void ft_add_node(t_token **tokens, t_token *new_node)
{
	t_token *temp;

	if (!new_node) //dont need as i check !new_token after I malloced it //but maybe if other functions dont check for NULL before passing?
		return;
	if (!*tokens) // If no tokens yet
	{
		*tokens = new_node;
		return;
	}
	temp = *tokens; //if we loop through *tokens, we will lose the pointer
	while (temp->next) // while temp->next != NULL, looping to find token->next == NULL
		temp = temp->next;
	temp->next = new_node; //each new_node has already NULL in theirs ->next, so no need to add NULL
}

t_token *ft_new_token(char *value, t_token_type type)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (printf("minishell: malloc has failed\n"), NULL);
	new->value = value; // check that value was malloced before
	new->type = type;
	new->quote = Q_NONE; // Default value
	new->next = NULL;
	return (new);
}

int	ft_token_word(t_data *data, char **cursor)
{
	int i;
	char *word;
	t_token *new_token;

	i = 0;
	while ((*cursor)[i] && !ft_special_char((*cursor)[i])) // starting, then ending the word with a special char
		i++;											   // the length of the word
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

int	ft_token_redir_in(t_data *data, char **cursor)
{
	int				i;
	char			*word;
	t_token			*new_token;
	t_token_type	type;
		
	i = 0;
	word = NULL;
	if ((*cursor)[i] == '<' && (*cursor)[i + 1] == '<')
	{
		word = ft_strdup("<<");
		i = 2;
		type = T_HEREDOC;
	}
	else if ((*cursor)[i] == '<')
	{
		word = ft_strdup("<");
		i = 1;
		type = T_REDIR_IN;
	}
	if (!word)
		return (printf("minishell: malloc has failed\n"), 1);
	new_token = ft_new_token(word, type);
	if (!new_token)
	{
		free(word);
		return (1);
	}
	ft_add_node(&data->tokens, new_token);
	*cursor += i;
	return (0);
}


int	ft_token_redir_out(t_data *data, char **cursor)
{
	int				i;
	char			*word;
	t_token			*new_token;
	t_token_type	type;
		
	i = 0;
	word = NULL;
	if ((*cursor)[i] == '>' && (*cursor)[i + 1] == '>')
	{
		word = ft_strdup(">>");
		i = 2;
		type = T_REDIR_APPEND;
	}
	else if ((*cursor)[i] == '>')
	{
		word = ft_strdup(">");
		i = 1;
		type = T_REDIR_OUT;
	}
	if (!word)
		return (printf("minishell: malloc has failed\n"), 1);
	new_token = ft_new_token(word, type);
	if (!new_token)
	{
		free(word);
		return (1);
	}
	ft_add_node(&data->tokens, new_token);
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
		while (*cursor && (*cursor == ' ' || (*cursor >= '\t' && *cursor <= '\r'))) //skip white space
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
			if (ft_token_redir_in(data, &cursor))  //start a redirect IN or HEREDOC token
				return (1);
		}
		else if (*cursor == '>')
		{
			if (ft_token_redir_out(data, &cursor))  //start a redirect OUT or APPEND token
				return (1);
		}

		
		//add quotes here
		else
		{
			//since we send an address of a cursor and parce through prompt, the pointer moves to the right position
			if (ft_token_word(data, &cursor))//start a word token, sending an address of a right cursor of propmt
				return (1); 
		}
	}
	
	
	return (0);
}

void	ft_print_tokens(t_data *data) //delete
{
	t_token *tmp;

	if (!data || !data->tokens)
		return ;
	tmp = data->tokens;
	while (tmp)
	{
		printf("type %d value %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
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

void ft_free(t_data *data)
{
	t_token *current;
	t_token *next_node;

	if (!data)
		return;

	current = data->tokens;
	while (current)
	{
		next_node = current->next; // Save address of next node
		if (current->value)
			free(current->value); // Free the string (the 'word')
		free(current);			  // Free the struct node itself
		current = next_node;	  // Move to the next saved address
	}
	data->tokens = NULL; // Reset head to NULL

	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

void	ft_init(char **envp, t_data *data)
{
	(void) envp;//add parcing envp
	//add more vars from header
	data->prompt = NULL;
	data->env = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	data->last_status = 0;
}


int	main(int ac, char **av, char **envp) //we need envp
{
	t_data	data;
	
	(void) av;
	
	ft_init(envp, &data);
	
	if (ac != 1)
	{
		printf("minishell: no arguments allowed\n");
		return (1);
	}
	while (1)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt) //ctrl D
			break;
		if (*data.prompt) //dont store empty commands
			add_history(data.prompt);
		if (ft_proccess_prompt(&data))
		{	
			ft_free(&data);
			data.last_status = 1;
			return(data.last_status);
		}
		ft_free(&data);
	}
	//clear_history(); //for MacOS
	rl_clear_history(); //for Linux
	return (data.last_status);
}
