/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:34:09 by dsalimov          #+#    #+#             */
/*   Updated: 2025/10/23 12:58:09 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_parse_cmd1(t_pipex *p, char *argv2)
{
	p->cmd1 = ft_split(argv2, ' ');
	if (!p->cmd1)
	{
		ft_err_exit("pipex: malloc error\n");
	}
}

void	ft_parse_cmd2(t_pipex *p, char *argv3)
{
	p->cmd2 = ft_split(argv3, ' ');
	if (!p->cmd2)
	{
		ft_free_mem(p->cmd1);
		ft_err_exit("pipex: malloc error\n");
	}
}

int	ft_forking(t_pipex *p, char **envp, int pfd[2])
{
	int	exit_code;

	p->pid1 = ft_fork_cmd1(p, envp, pfd);
	p->pid2 = ft_fork_cmd2(p, envp, pfd);
	close(pfd[0]);
	close(pfd[1]);
	ft_check_close_fdfile(p);
	p->wp1 = waitpid(p->pid1, &p->wstatus1, 0);
	p->wp2 = waitpid(p->pid2, &p->wstatus2, 0);
	ft_free_mem_free_path(p);
	if (p->wp1 == -1 || p->wp2 == -1) //how to check
	{
		perror("pipex: waitpid");
		exit(1);
	}
	if (WIFEXITED(p->wstatus2)) //returns true if exited normally
		exit_code = WEXITSTATUS(p->wstatus2);
	else
		exit_code = 1;
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		pfd[2];
	int		exit_code;

	if (argc != 5)
		ft_err_exit("pipex: usage error: ./pipex file1 cmd1 cmd2 file2\n");
	ft_init_struct(&p);
	ft_parse_cmd1(&p, argv[2]); //malloc p->cmd1
	ft_parse_cmd2(&p, argv[3]); //malloc p->cmd1
	ft_syntax_check(&p); //shell check it before anything else
	ft_check_direct_path1(&p); //check "" and /
	ft_check_direct_path2(&p); //check "" and /
	ft_check_files(&p, argv); //if (fd_file1 = -1 && ft_file2 = -1) exit
	ft_get_path(&p, envp);
	if (pipe(pfd) == -1)
	{
		perror("pipex: pipe");
		ft_check_close_fdfile(&p);
		ft_free_mem_free_path(&p);
		exit(1);
	}
	exit_code = ft_forking(&p, envp, pfd);
	return (exit_code);
}
