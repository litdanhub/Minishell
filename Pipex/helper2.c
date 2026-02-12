/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:52:46 by dsalimov          #+#    #+#             */
/*   Updated: 2026/01/20 15:43:39 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_split_path(t_pipex *p, char **envp)
{
	int		i;
	char	*new_envp;
	char	**path_all;

	i = 0;
	while (envp[i] && (ft_strncmp("PATH=", envp[i], 5) != 0)) // finding "PATH="
		i++;
	if (!envp[i])
		ft_free_err_exit(p, "pipex: PATH not found in envp or no envp\n");
	new_envp = envp[i] + 5; // skipping PATH= by pointing on 5 elements futher
	path_all = ft_split(new_envp, ':');
	if (!path_all)
		ft_free_err_exit(p, "pipex: malloc error\n");
	return (path_all);
}

void	ft_check_direct_path1(t_pipex *p)
{
	if (p->cmd1[0] == NULL) //""
	{
		p->cmd1_true = 0;
		p->exit_code1 = 127; //no need ft_get_path
	}
	else if (ft_strchr(p->cmd1[0], '/') != NULL) //we have path1
	{
		p->path1 = ft_strdup(p->cmd1[0]);
		if (!p->path1)
		{
			ft_free_mem_free_path(p);
			ft_err_exit("pipex: malloc error\n");
		}
		p->cmd1_true = 1;
	}
}

void	ft_check_direct_path2(t_pipex *p)
{
	if (p->cmd2[0] == NULL) //""
	{
		p->cmd2_true = 0;
		p->exit_code2 = 127;//no need ft_get_path
	}
	else if (ft_strchr(p->cmd2[0], '/') != NULL) //we have path2
	{
		p->path2 = ft_strdup(p->cmd2[0]);
		if (!p->path2)
		{
			ft_free_mem_free_path(p);
			ft_err_exit("pipex: malloc error\n");
		}
		p->cmd2_true = 1;
	}
}

void	ft_dup2_cmd2(t_pipex *p, int pfd[2])
{
	close(pfd[1]);
	if (p->fd_file2 == -1)
		ft_clean_and_exit_cmd(p, 0, pfd);
	if (dup2(pfd[0], 0) == -1)
	{
		perror("pipex: dup2");
		ft_clean_and_exit_cmd(p, 0, pfd);
	}
	if (dup2(p->fd_file2, 1) == -1)
	{
		perror("pipex: dup2");
		ft_clean_and_exit_cmd(p, 0, pfd);
	}
	close(pfd[0]);
	ft_check_close_fdfile(p);
}
