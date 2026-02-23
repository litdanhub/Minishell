/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:22:25 by dsalimov          #+#    #+#             */
/*   Updated: 2026/02/23 18:47:58 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

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
