/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:46:18 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/12 16:35:45 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
}

void	ft_init(char **envp, t_data *data)
{
	(void) envp;//do it
	//add more vars from header
	data->prompt = NULL;
	data->env = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	data->last_status = 0;
}

int	ft_proccess_prompt(t_data *data)
{
	printf("%s\n", data->prompt);
	return (0);
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
	rl_clear_history();
	return (data.last_status);
}