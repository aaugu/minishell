/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:15 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/17 11:04:02 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_exit(t_data *data, char **cmd_args, int cmd_nbr)
{
	if (cmd_nbr == 1 && ft_strs_len(cmd_args) == 1)
	{
		printf("exit\n");
		clear_minishell(data);
	}
}
