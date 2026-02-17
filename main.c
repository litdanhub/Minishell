/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:46:18 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/17 18:07:06 by dsalimov         ###   ########.fr       */
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

int	ft_token_pipe(t_data *data, char **cursor)
{
	(void) data;
	(void) *cursor;

	return (0);
}


int	ft_token_redir(t_data *data, char **cursor)
{
	(void) data;
	(void) *cursor;

	return (0);
}

int ft_special_char(char c) //maybe add quotes here?
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

/*
Every time you identify a WORD, PIPE, or REDIR, you:
Create the node (malloc).
Fill the node (type = T_PIPE, value = "|", etc.).
Call ft_add_token_back(&data->tokens, new_node);.
*/


void ft_add_token_back(t_token **tokens, t_token *new_node)
{
    t_token *temp;

    if (!new_node)
        return ;
    if (!*tokens) // If the train is empty
    {
        *tokens = new_node;
        return ;
    }
    temp = *tokens;
    while (temp->next) // Find the last car
        temp = temp->next;
    temp->next = new_node; // Hook the new car onto the back
}

/*void ft_token_word(t_data *data, char **cursor)
{
    int     len;
    char    *word_val;
    t_token *new_node;

    
    // 2. Create and Add the token


    // 3. PUSH the cursor forward by the amount of characters we just 'ate'
    *cursor += len;
}*/


t_token *ft_new_token(char *value, t_token_type type)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (printf("minishell: malloc has failed\n"), NULL);
	new->value = value; // We assume 'value' was already malloc'd (like by ft_substr)
	new->type = type;
	new->quote = Q_NONE; // Default value
	new->next = NULL;
	return (new);
}

int	ft_token_word(t_data *data, char **cursor)
{
	int		i;
	char	*word;
	t_token	*new_token;
	
	i = 0;
	while ((*cursor)[i] && !ft_special_char((*cursor)[i])) //starting, then ending a word with a special char
		i++; //the length of a word
	word = ft_substr(*cursor, 0, i);
	if (!word)
		return (printf("minishell: malloc has failed\n"), 1); //free all nodes created
	
	new_token = ft_new_token(word, T_WORD);
	if (!new_token)
		return (1);
    ft_add_token_back(&(data->tokens), new_node);
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
			ft_token_pipe(data, &cursor); //start a pipe token
		}
		else if (*cursor == '<' || *cursor == '>')
		{
			ft_token_redir(data, &cursor); //start a redirect token
		}
		else
		{
			//since we send an address of a cursor and parce through prompt, the pointer moves to the right position
			if (ft_token_word(data, &cursor))//start a word token, sending an address of a right cursor of propmt
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
	
	return (0);
}


void	ft_free(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
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
			return(data.last_status);
		}
		ft_free(&data);
	}
	//clear_history(); //for MacOS
	rl_clear_history(); //for Linux
	return (data.last_status);
}
