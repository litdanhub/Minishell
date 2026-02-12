/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:35:11 by dsalimov          #+#    #+#             */
/*   Updated: 2025/10/22 15:22:52 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_err_exit(t_pipex *p, char *s)
{
	ft_check_close_fdfile(p);
	ft_free_mem_free_path(p);
	ft_err_exit(s);
}

void	ft_err_exit(char *s)
{
	write(2, s, ft_strlen(s));
	exit(1);
}

void	ft_free_mem(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	ft_check_close_fdfile(t_pipex *p)
{
	if (p->fd_file1 != -1)
		close(p->fd_file1);
	if (p->fd_file2 != -1)
		close(p->fd_file2);
}

void	ft_init_struct(t_pipex *p) //add more vars
{
	p->cmd1 = NULL;
	p->cmd2 = NULL;
	p->path1 = NULL;
	p->path2 = NULL;
	p->cmd1_true = -1; //-1 uninitial, 0 false, 1 true
	p->cmd2_true = -1;
	p->exit_code1 = 0;
	p->exit_code2 = 0;
	p->fd_file1 = -1; //gpt advise. Do i need it???
	p->fd_file2 = -1;
}
