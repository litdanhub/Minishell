/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:54:47 by dsalimov          #+#    #+#             */
/*   Updated: 2025/10/23 13:10:01 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_pipex
{
	int		fd_file1;
	int		fd_file2;
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
	int		cmd1_true;
	int		cmd2_true;
	int		exit_code1;
	int		exit_code2;
	int		pid1;
	int		pid2;
	int		wstatus1;
	int		wstatus2;
	int		wp1;
	int		wp2;
}	t_pipex;

//utils.c
void	ft_free_err_exit(t_pipex *p, char *s);
void	ft_err_exit(char *s);
void	ft_free_mem(char **arr);
void	ft_check_close_fdfile(t_pipex *p);
void	ft_init_struct(t_pipex *p);

//helper.c
void	ft_check_files(t_pipex *p, char **argv);
void	ft_print_cmd_not_found(t_pipex *p, int i);
void	ft_clean_and_exit_cmd(t_pipex *p, int i, int pfd[2]);
void	ft_syntax_check(t_pipex *p);
void	ft_free_mem_free_path(t_pipex *p);

//helper2.c
char	**ft_split_path(t_pipex *p, char **envp);
void	ft_check_direct_path1(t_pipex *p);
void	ft_check_direct_path2(t_pipex *p);
void	ft_dup2_cmd2(t_pipex *p, int pfd[2]);

//path.c
void	ft_get_path(t_pipex *p, char **envp);
int		ft_search_path1(t_pipex *p, char **path_all);
int		ft_search_path2(t_pipex *p, char **path_all);
int		ft_check_cmd1(t_pipex *p, char *path_one);
int		ft_check_cmd2(t_pipex *p, char *path_one);

//exec.c
void	ft_exec_cmd1(t_pipex *p, char **envp, int pfd[2]);
int		ft_fork_cmd1(t_pipex *p, char **envp, int pfd[2]);
void	ft_exec_cmd2(t_pipex *p, char **envp, int pfd[2]);
int		ft_fork_cmd2(t_pipex *p, char **envp, int pfd[2]);
void	ft_dup2_cmd1(t_pipex *p, int pfd[2]);

//main.c
void	ft_parse_cmd1(t_pipex *p, char *argv2);
void	ft_parse_cmd2(t_pipex *p, char *argv3);
int		ft_forking(t_pipex *p, char **envp, int pfd[2]);

#endif