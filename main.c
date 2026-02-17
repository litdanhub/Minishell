/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:46:18 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/15 12:21:32 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*The shell inherits environment variables from its parent. We must duplicate them into our t_env list.
Increment SHLVL: We must look for the SHLVL variable. If it exists, parse it to an integer, 
increment it, and store it back. This tells the user they are in a nested shell.
Missing Env: If the shell is started with env -i./minishell (empty environment), 
we must manually create PWD, SHLVL=1, and _=/usr/bin/env to prevent crashes. */  


#include "minishell.h"

//echo 'hello'
//echo 'hello
//echo "hello"
//echo "hello
//echo 'hello"hello"' 
int	ft_unclosed_quotes(t_data *data)
{
	int	i;
	int	type;

	i = 0;
	type = Q_NONE; //not found yet
	while (data->prompt[i] && data->prompt[i] != '\'' && data->prompt[i] != '"') //looking for opening quote
		i++;
	if (data->prompt[i] == '\0')
		return (0); //no quotes at all
	else if (data->prompt[i] == '\'')
		type = Q_SINGLE;
	else if (data->prompt[i] == '"')
		type = Q_DOUBLE;

	i++;
	//look for closing quotes and run this ft_uclosed_quotes until EOF
	while (data->prompt[i] && data->prompt[i] != '\'' && data->prompt[i] != '"')
		i++;
	if (data->prompt[i] == '\0')
	{	
		return (1); //didn't find closing quotes either type
	}
	return (0);
}

int	ft_proccess_prompt(t_data *data)
{
	//int	i;
	
	if (ft_unclosed_quotes(data)) //found in general unclosed quotes
	{
		printf("minishell: syntax error: unclosed quotes\n");
		return (0);
	}
	//i = 0;
	//while (data->prompt[i])
	//{
	//}
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
	clear_history(); //for MacOS
	//rl_clear_history(); //for Linux
	return (data.last_status);
}