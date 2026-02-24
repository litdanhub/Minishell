/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:46:18 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/24 15:00:16 by dsalimov         ###   ########.fr       */
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


int	ft_proccess_prompt(t_data *data)
{
	if (ft_lexing(data))
		return (1);
	printf("=======LEXING=========\n");
	ft_print_tokens(data); //delete
	printf("=======PARSING=========\n");
		
	if (ft_parsing(data))
		return (1);
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
		
	if (argc != 1)
		return (ft_print_error("no arguments allowed"), 1);
	ft_init_data(&data);
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
			ft_cleanup(&data); //add free cmd
			break ;
		}
		if (*data.prompt) //don't store empty commands
			add_history(data.prompt);
		if (ft_proccess_prompt(&data))
		{
			ft_cleanup(&data); //now i free everything in case of return 1 (malloc error)
			data.last_status = 1;
			return (data.last_status);
		}
		ft_free_tokens(&data); //add free cmd
		ft_free_prompt(&data);
	}
	//clear_history(); //for MacOS
	rl_clear_history(); //for Linux
	return (data.last_status);
}
