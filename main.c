/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:46:18 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/19 20:23:31 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//for printing error msg use ft_print_error(char *msg)

int	main(int ac, char **av, char **envp) //we need envp
{
	t_data	data;

	(void) av;
	if (ac != 1)
		return (ft_print_error("no arguments allowed"), 1);
	ft_init(&data);
	if (ft_init_envp(&data, envp))
		return(1);
	while (1)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt) //ctrl+D
			break ;
		if (*data.prompt) //don't store empty commands
			add_history(data.prompt);
		if (ft_proccess_prompt(&data))
		{
			ft_free(&data);
			data.last_status = 1;
			return (data.last_status);
		}
		ft_free(&data);
	}
	//clear_history(); //for MacOS
	rl_clear_history(); //for Linux
	return (data.last_status);
}
