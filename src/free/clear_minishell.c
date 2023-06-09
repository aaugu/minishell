/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:54:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/08 13:38:18 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing_input.h"

/* Handles the clear of every allocated memory in program */
void	clear_minishell(t_data *data)
{
	rl_clear_history();
	if (data->envp)
		ft_strs_free(data->envp, data->env_size);
	if (data->cmd)
		ft_strs_free(data->cmd, ft_strs_len(data->cmd));
	if (data->all_path)
		ft_strs_free(data->all_path, ft_strs_len(data->all_path));
	if (data->user_input)
		free(data->user_input);
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->trash_path)
		free(data->trash_path);
	if (data->fd_array)
		free(data->fd_array);
	exit(g_exit_code);
}
