/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:47 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/18 13:19:44 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

# include <stdio.h> //readline
# include <readline/readline.h>
# include <readline/history.h>

# include <unistd.h>//do i need all these libs?
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

//IF CHANGE STRUCTS ADD IN FT_INIT

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,      // <
	T_REDIR_OUT,     // >
	T_REDIR_APPEND,  // >>
	T_HEREDOC        // <<
}	t_token_type;

typedef enum e_quote_type
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_type;

typedef struct s_redir
{
	t_token_type		type;     // IN / OUT / APPEND / HEREDOC
	char				*target;  // filename or delimiter
	int					fd;       // opened fd (if needed)
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;     // NULL terminated
	char			*path;      // full executable path (if not builtin)
	t_redir			*redirs;    // linked list of redirections
	int				infile;     // default STDIN_FILENO
	int				outfile;    // default STDOUT_FILENO
	struct s_cmd	*next;      // next command in pipeline
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	t_quote_type		quote;   // useful for expansion logic
	struct s_token		*next;
}	t_token;

typedef struct s_data 
{
	char			*prompt;
	t_env			*env;          // linked list envp
	t_token			*tokens;       // token list from lexer
	t_cmd			*cmds;         // parsed commands (pipeline)
	t_quote_type	quote_type; //do i need it?
	int				last_status;   // same as g_status but stored locally
}	t_data;

#endif