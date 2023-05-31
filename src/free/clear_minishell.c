/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:54:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/31 11:39:23 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing_input.h"

void	clear_minishell(t_data *data)
{
	rl_clear_history();
	if (data->envp)
		ft_strs_free(data->envp, data->env_size);
	if (data->cmd)
		ft_strs_free(data->cmd, ft_strs_len(data->cmd));
	if (data->user_input)
		free(data->user_input);
	if (data->fd_array)
		free(data->fd_array);
	exit(g_exit_code);
}
