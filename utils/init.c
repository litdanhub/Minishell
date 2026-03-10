/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsalimov <dsalimo@student.42vienna.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:10:04 by dsalimov          #+#    #+#             */
/*   Updated: 2026/03/10 11:39:17 by dsalimov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_init_data(t_data *data)
{
	//add more vars to initialize
	data->prompt = NULL;
	data->env = NULL;
	data->tokens = NULL;
	data->cmds = NULL;
	data->exit_code = 0;
}
