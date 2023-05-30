/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:15 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/30 09:40:35 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../libft/libft.h"

/*
Exit in bash : The exit() function causes normal process termination and the
least significant byte of status (i.e., status & 0xFF) is returned to the parent,
here it is 
 */

int	cmd_exit(t_data *data, char **cmd_args, int cmd_nbr)
{
	if (cmd_nbr == 1)
	{
		printf("exit\n");
		if (ft_strs_len(cmd_args) == 1)
			clear_minishell(data);
		else if (ft_strs_len(cmd_args) == 2)
		{
			g_exit_code = print_err("minishell: exit: asd: numeric argument required", 255);
		}
		else if (ft_strs_len(cmd_args) >= 2)
		{
			g_exit_code = print_err("minishell: exit: too many arguments", 0);
		}
	}
}
