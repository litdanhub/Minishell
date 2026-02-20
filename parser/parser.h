/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:19:39 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/20 17:05:29 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

//lexer.c
void	ft_print_tokens(t_data *data);//delete
int		ft_special_char(char c); //check this function and ft_isspace
int		ft_isspace(char c);
void	ft_add_node(t_token **tokens, t_token *new_node);
t_token	*ft_new_token(char *value, t_token_type type);
int		ft_token_word(t_data *data, char **cursor);
int		ft_token_redir_in(t_data *data, char **cursor);
int		ft_token_redir_out(t_data *data, char **cursor);
int		ft_token_pipe(t_data *data, char **cursor);
int		ft_lexing(t_data *data);
int		ft_proccess_prompt(t_data *data);

#endif