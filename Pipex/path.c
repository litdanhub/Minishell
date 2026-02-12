/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:27:59 by dsalimov          #+#    #+#             */
/*   Updated: 2025/10/23 12:57:46 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_get_path(t_pipex *p, char **envp)
{
	int		result1;
	int		result2;
	int		i;
	char	**path_all;

	i = 0;
	result1 = 0;
	result2 = 0;
	if (!envp || !envp[i])
		return ;
	path_all = ft_split_path(p, envp);
	if (p->cmd1_true == -1) //uninitial, meaning chech the path
		result1 = ft_search_path1(p, path_all); //check cmd1
	if (p->cmd2_true == -1) //uninitial, meaning check the path
		result2 = ft_search_path2(p, path_all); //check cmd2
	if (result1 == 0 && p->cmd1_true == -1)
		p->exit_code1 = 127;
	if (result2 == 0 && p->cmd2_true == -1 && p->exit_code2 != 1)
		p->exit_code2 = 127;
	ft_free_mem(path_all);
}

int	ft_search_path1(t_pipex *p, char **path_all)
{
	int	i;
	int	result1;

	i = 0;
	result1 = 0;
	while (path_all[i] && result1 != 100)
	{
		result1 = ft_check_cmd1(p, path_all[i]);
		if (result1 == 1) //malloc error
		{
			ft_free_mem(path_all);
			ft_free_err_exit(p, "pipex: malloc error\n");
		}
		else if (result1 == 0) //keep looking
			free(p->path1);
		i++;
	}
	return (result1);
}

int	ft_search_path2(t_pipex *p, char **path_all)
{
	int	i;
	int	result2;

	i = 0;
	result2 = 0;
	while (path_all[i] && result2 != 200)
	{
		result2 = ft_check_cmd2(p, path_all[i]);
		if (result2 == 1) //malloc error
		{
			ft_free_mem(path_all);
			ft_free_err_exit(p, "pipex: malloc error\n");
		}
		else if (result2 == 0) //keep looking
			free(p->path2);
		i++;
	}
	return (result2);
}

int	ft_check_cmd1(t_pipex *p, char *path_one)
{
	char	*temp_path1;

	temp_path1 = ft_strjoin(path_one, "/");
	if (!temp_path1)
		return (1);
	p->path1 = ft_strjoin(temp_path1, (const char *)p->cmd1[0]);
	free (temp_path1);
	if (!p->path1)
		return (1);
	if (access(p->path1, F_OK) == 0)
	{
		p->cmd1_true = 1;
		return (100); //cmd1 found
	}
	return (0);
}

int	ft_check_cmd2(t_pipex *p, char *path_one)
{
	char	*temp_path2;

	temp_path2 = ft_strjoin(path_one, "/");
	if (!temp_path2)
		return (1);
	p->path2 = ft_strjoin(temp_path2, (const char *)p->cmd2[0]);
	free(temp_path2);
	if (!p->path2)
		return (1);
	if (access(p->path2, F_OK) == 0)
	{
		p->cmd2_true = 1;
		return (200); //cmd2 found
	}
	return (0);
}
