/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:45:48 by dsalimov          #+#    #+#             */
/*   Updated: 2025/10/23 13:01:09 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_cmd1(t_pipex *p, char **envp, int pfd[2])
{
	ft_dup2_cmd1(p, pfd);
	if (p->cmd1_true == 1) // resolved by parent already, cmd1 was found
	{
		if (execve(p->path1, p->cmd1, envp) == -1)
		{
			if (errno == EACCES)
				p->exit_code1 = 126;
			else if (errno == ENOENT)
				p->exit_code1 = 127;
			else
				p->exit_code1 = 1;
			write(2, "pipex: ", 7);
			perror(p->cmd1[0]);
		}
	}
	else // cmd1 was not found earlier by parent
	{
		ft_print_cmd_not_found(p, 1);
		p->exit_code1 = 127;
	}
	ft_free_mem_free_path(p);
	exit(p->exit_code1);
}

int	ft_fork_cmd1(t_pipex *p, char **envp, int pfd[2])
{
	int	pid1;

	pid1 = fork();
	if (pid1 == -1) //how to check
	{
		perror("pipex: fork");
		ft_clean_and_exit_cmd(p, 2, pfd);
	}
	if (pid1 == 0)
		ft_exec_cmd1(p, envp, pfd);
	return (pid1);
}

void	ft_exec_cmd2(t_pipex *p, char **envp, int pfd[2])
{
	ft_dup2_cmd2(p, pfd);
	if (p->cmd2_true == 1) // cmd2 was found by parent already
	{
		if (execve(p->path2, p->cmd2, envp) == -1)
		{
			if (errno == EACCES)
				p->exit_code2 = 126;
			else if (errno == ENOENT)
				p->exit_code2 = 127;
			else
				p->exit_code2 = 1;
			write(2, "pipex: ", 7);
			perror(p->cmd2[0]);
		}
	}
	else // cmd2 was not found earlier by parent
	{
		ft_print_cmd_not_found(p, 2);
		if (p->exit_code2 != 1)
			p->exit_code2 = 127;
	}
	ft_free_mem_free_path(p);
	exit(p->exit_code2);
}

int	ft_fork_cmd2(t_pipex *p, char **envp, int pfd[2])
{
	int	pid2;

	pid2 = fork();
	if (pid2 == -1) //how to check
	{
		perror("pipex: fork");
		ft_clean_and_exit_cmd(p, 2, pfd);
	}
	if (pid2 == 0)
		ft_exec_cmd2(p, envp, pfd);
	return (pid2);
}

void	ft_dup2_cmd1(t_pipex *p, int pfd[2])
{
	close(pfd[0]);
	if (p->fd_file1 == -1)
		ft_clean_and_exit_cmd(p, 1, pfd);
	if (dup2(p->fd_file1, 0) == -1)
	{
		perror("pipex: dup2");
		ft_clean_and_exit_cmd(p, 1, pfd);
	}
	if (dup2(pfd[1], 1) == -1)
	{
		perror("pipex: dup2");
		ft_clean_and_exit_cmd(p, 1, pfd);
	}
	close(pfd[1]);
	ft_check_close_fdfile(p);
}
