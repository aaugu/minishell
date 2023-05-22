/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:15 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/22 13:37:54 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Exit in bash : The exit() function causes normal process termination and the
least significant byte of status (i.e., status & 0xFF) is returned to the parent,
here it is 
 */

int	cmd_exit(t_data *data, char **cmd_args, int cmd_nbr)
{
	if (cmd_nbr == 1 && ft_strs_len(cmd_args) == 1)
	{
		printf("exit\n");
		clear_minishell(data);
	}
}
