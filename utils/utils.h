/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:17:43 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/23 17:36:06 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"

//utils.c
void	ft_print_error(char *msg); //printig error msgs

//free.c
void	ft_free_tokens(t_data *data);
void	ft_free_prompt(t_data *data);
void	ft_free_env(t_data *data);

//init.c
void	ft_init(t_data *data); //initializing variables

#endif
