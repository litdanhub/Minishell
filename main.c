/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:46:18 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/19 17:03:36 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp) //we need envp
{
	t_data	data;

	(void) av;
	ft_init(envp, &data);
	if (ac != 1)
		return (printf("minishell: no arguments allowed\n"), 1);
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
