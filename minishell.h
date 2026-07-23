/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:47 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/19 22:13:09 by dsalimov         ###   ########.fr       */
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

//PARSER//
//lexer.c
void	ft_print_tokens(t_data *data);//delete
int		ft_special_char(char c);
int		ft_isspace(char c);
void	ft_add_token_node(t_token **tokens, t_token *new_node);
t_token	*ft_new_token(char *value, t_token_type type, int quotes);
int		ft_token_word(t_data *data, char **cursor);
int		ft_token_redir_in(t_data *data, char **cursor);
int		ft_token_redir_out(t_data *data, char **cursor);
int		ft_token_pipe(t_data *data, char **cursor);
int		ft_expand(t_data *data, char **cursor, int *i, char **word);
int		ft_expand_var(t_data *data, char **cursor, int *i, char **word);
char	*ft_append_word(char *word, char *str);
char	*ft_append_char(char *word, char c);
int		ft_lexing(t_data *data);

//parser.c
int		ft_parsing(t_data *data);
void	ft_print_cmd(t_data *data); //delete after use

//parser_utils.c
t_redir	*ft_new_redir(char *value, t_token_type type, int quotes);
void	ft_add_redir_node(t_redir **redir, t_redir *new_node);
t_cmd	*ft_new_cmd(char **argv);
void	ft_add_cmd_node(t_cmd **cmd, t_cmd *new_node);

//checker.c
int		ft_check_lexing(t_data *data);

//EXEC
//heredoc.c
int		ft_heredoc(t_data *data);
int		ft_loop_readline(t_data *data, char *delim, int quoted);

//UTILS
//utils.c
void	ft_print_error(char *msg); //printig error msgs

//free.c
void	ft_free_tokens(t_data *data);
void	ft_free_prompt(t_data *data);
void	ft_free_env(t_data *data);
void	ft_free_cmds(t_data *data);

//init.c
void	ft_init_data(t_data *data); //initializing variables

//BUILTINS
//builtins.c
char	*ft_pwd(void);
void	ft_env(t_data *data);

//env.c
void	ft_free_key_value(char *key, char *value);
int		ft_init_envp(t_data *data, char **envp, char *argv);
int		ft_parse_env(char *envp, char **key, char **value);

//no_env.c
int		ft_add_env_pwd(t_data *data);
int		ft_add_env_shlvl(t_data *data);
int		ft_add_env_underscore_absolute(t_data *data, char *argv);
int		ft_add_env_unders_rel(t_data *data, char *argv, char *key, char *tmp);
int		ft_no_env(t_data *data, char *argv);

//env_utils.c
t_env	*ft_env_search_key(t_data *data, char *search); //searches for KEY in env and returns *node
void	ft_add_env_node(t_env **env, t_env *new_node);
t_env	*ft_new_env(char *key, char *value);


#endif
