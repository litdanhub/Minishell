/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:47 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/19 15:21:21 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h" //stdlib.h <stdint.h> <unistd.h>
# include <stdio.h> //readline, printf
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h> //open
# include <sys/types.h> //open, fork
# include <sys/wait.h> //wait
# include <string.h> //strerror
# include <errno.h> //perror
# include <signal.h> //signal
# include <limits.h> //PATH_MAX



typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN, //<
	T_REDIR_OUT, //>
	T_REDIR_APPEND, //>>
	T_HEREDOC //<<
}	t_token_type;

typedef enum e_quote_type
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_type;

typedef struct s_redir
{
	t_token_type	type;// IN / OUT / APPEND / HEREDOC
	char			*target;// filename or delimiter
	int				quoted; //if !0 (quoted), don't expand inside HEREDOC
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd //for execve(path, argv, t_env->envp )
{
	char			**argv;// has to be malloced and NULL terminated
	char			*path;// full executable path (if not builtin)
	t_redir			*redirs;// linked list of redirections
	int				infile;// 0, change during open()
	int				outfile;// 1, change during open()
	struct s_cmd	*next;// next command in pipeline
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote; //only for heredoc: 1 - dont expand, 0 - expand
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char			*prompt;
	t_env			*env;
	t_token			*tokens;
	t_cmd			*cmds;
	t_quote_type	quote_type;
	int				exit_code;//last exit code
}	t_data;

#endif
