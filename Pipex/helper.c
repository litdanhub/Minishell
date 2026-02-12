/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:46:13 by dsalimov          #+#    #+#             */
/*   Updated: 2025/10/22 16:17:58 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_files(t_pipex *p, char **argv)
{
	p->fd_file2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);//trunc and 0644 = this is how shell does
	if (p->fd_file2 == -1)
	{
		write(2, "pipex: ", 7);
		perror(argv[4]);
		p->exit_code2 = 1;
	}
	p->fd_file1 = open(argv[1], O_RDONLY);
	if (p->fd_file1 == -1)
	{
		write(2, "pipex: ", 7);
		perror(argv[1]);
	}
	if (p->fd_file1 == -1 && p->fd_file2 == -1)
	{
		ft_free_mem_free_path(p);
		exit(1);
	}
}

void	ft_print_cmd_not_found(t_pipex *p, int i)
{
	write(2, "pipex: ", 7);
	if (i == 1 && p->cmd1[0] != NULL)
		write(2, p->cmd1[0], ft_strlen(p->cmd1[0]));
	else if (i == 2 && p->cmd2[0] != NULL)
		write(2, p->cmd2[0], ft_strlen(p->cmd2[0]));
	else
		write(2, " ", 1);
	write(2, ": command not found\n", 20);
}

void	ft_clean_and_exit_cmd(t_pipex *p, int i, int pfd[2])
{
	if (i == 0)
		close(pfd[0]);
	else if (i == 1)
		close(pfd[1]);
	else if (i == 2)
	{
		close(pfd[0]);
		close(pfd[1]);
	}
	ft_check_close_fdfile(p);
	ft_free_mem_free_path(p);
	exit(1);
}

void	ft_syntax_check(t_pipex *p)
{
	if (!p->cmd1 || !p->cmd1[0] || !p->cmd2 || !p->cmd2[0])
		return ;
	if (p->cmd1[0][0] == ';' || p->cmd1[0][0] == '|' || p->cmd1[0][0] == '>' ||
		p->cmd1[0][0] == '<' || p->cmd1[0][0] == '&' ||
		p->cmd2[0][0] == ';' || p->cmd2[0][0] == '|' || p->cmd2[0][0] == '>' ||
		p->cmd2[0][0] == '<' || p->cmd2[0][0] == '&')
	{
		write(2, "pipex: syntax error near unexpected token\n", 42);
		ft_free_mem(p->cmd1);
		ft_free_mem(p->cmd2);
		exit(2);
	}
}

void	ft_free_mem_free_path(t_pipex *p)
{
	ft_free_mem(p->cmd1);
	ft_free_mem(p->cmd2);
	if (p->cmd1_true != -1)
		free(p->path1);
	if (p->cmd2_true != -1)
		free(p->path2);
}
