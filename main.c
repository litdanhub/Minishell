/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:46:18 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/12 17:05:47 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"
#include "exec/exec.h"
#include "builtins/builtins.h"
#include "utils/utils.h"

void	ft_cleanup_exit(t_data *data)
{
	ft_free_cmds(data);
	ft_free_tokens(data);
	ft_free_prompt(data);
	ft_free_env(data);
}

void	ft_cleanup_iteration(t_data *data)
{
	ft_free_cmds(data);
	ft_free_tokens(data);
	ft_free_prompt(data);
}

void	ft_print_env(t_data *data) //delete after use
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		printf("%s = %s\n", env->key, env->value);
		env = env->next;
	}
}

int	ft_process_prompt(t_data *data)
{
	
	data->exit_code = ft_lexing(data);
	if (data->exit_code) //1 malloc err, 2 syntax err
		return (data->exit_code);
		
	ft_print_tokens(data); //delete
	if (ft_check_lexing(data)) //returns 2 if syntax err
	{	
		data->exit_code = 2;
		return (2);
	}

	if (ft_parsing(data)) //return 1 if malloc err
	{
		data->exit_code = 1;
		return (1);
	}
	ft_print_cmd(data); //delete
	
	

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
	//ft_print_env(&data); //delete
	while (1)
	{
		printf("\n"); //delete
		data.prompt = readline("minishell$ ");
		if (!data.prompt) //ctrl+D
		{	
			ft_cleanup_exit(&data);
			break ;
		}
		if (*data.prompt) //don't store empty commands
			add_history(data.prompt);
			
		//data.last_status = ft_process_prompt(&data); //1 malloc err, 2 syntax err
		ft_process_prompt(&data);
		if (data.exit_code == 1) //malloc error
		{
			ft_cleanup_exit(&data);
			break ;
		}
		ft_cleanup_iteration(&data);
		printf("-=EXIT CODE=- %d\n", data.exit_code); //delete
	}
	clear_history(); //for MacOS
	//rl_clear_history(); //for Linux
	return (data.exit_code);
}

/*
/////////test for funcheck(instead of readline)/////////////
	int		i = 0;
	while (i < 30)
	{
		data.prompt = ft_strdup("echo \"Hello world\" | $USER $eeee 111$USER1111 | wc -l");
		if (!data.prompt)
		{
			ft_cleanup_exit(&data);
			return(1);
		}
		
		ft_process_prompt(&data);
		
		if (data.exit_code == 1)
		{
			ft_cleanup_exit(&data);
			break ;
		}
		ft_cleanup_iteration(&data);
		printf("-=EXIT CODE=- %d\n", data.exit_code);
		i++;
	}
	ft_free_env(&data);
	return (data.exit_code);
}
////////////////////////////////////////////////////////
*/
