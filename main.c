/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:46:18 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/23 21:30:35 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"
#include "exec/exec.h"
#include "builtins/builtins.h"
#include "utils/utils.h"

void	ft_cleanup(t_data *data)
{
	ft_free_env(data);
	ft_free_tokens(data);
	ft_free_prompt(data);
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	if (argc != 1)
		return (ft_print_error("no arguments allowed"), 1);
	ft_init(&data);
	if (ft_init_envp(&data, envp, argv[0]))
	{
		ft_free_env(&data);
		return(1);
	}
	while (1)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt) //ctrl+D
		{	
			ft_cleanup(&data);
			break ;
		}
		if (*data.prompt) //don't store empty commands
			add_history(data.prompt);
		if (ft_proccess_prompt(&data))
		{
			ft_cleanup(&data);
			data.last_status = 1;
			return (data.last_status);
		}
		ft_cleanup(&data);
	}
	//clear_history(); //for MacOS
	rl_clear_history(); //for Linux
	return (data.last_status);
}
