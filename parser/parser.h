/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:19:39 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/27 18:40:30 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

//lexer.c
void	ft_print_tokens(t_data *data);//delete
int		ft_special_char(char c); //check this function and ft_isspace
int		ft_isspace(char c);
void	ft_add_token_node(t_token **tokens, t_token *new_node);
t_token	*ft_new_token(char *value, t_token_type type);
int		ft_token_word(t_data *data, char **cursor);
int		ft_token_redir_in(t_data *data, char **cursor);
int		ft_token_redir_out(t_data *data, char **cursor);
int		ft_token_pipe(t_data *data, char **cursor);
int		ft_lexing(t_data *data);

//parser.c
int		ft_parsing(t_data *data);
void	ft_print_cmd(t_data *data); //delete after use

//parser_utils.c
t_redir	*ft_new_redir(char *value, t_token_type type);
void	ft_add_redir_node(t_redir **redir, t_redir *new_node);
t_cmd	*ft_new_cmd(char **argv);
void	ft_add_cmd_node(t_cmd **cmd, t_cmd *new_node);

//checker.c
int		ft_check_lexing(t_data *data);


#endif
