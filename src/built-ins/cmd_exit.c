/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:15 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/30 13:51:20 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../includes/print_error.h"
#include "../../libft/libft.h"

void	get_exit_code(t_data *data, char **cmd_args);

/*
Exit in bash : The exit() function causes normal process termination and the
least significant byte of status (i.e., status & 0xFF) is returned to the parent,
here it is 
 */
void	cmd_exit(t_data *data, char **cmd_args, int cmd_nbr)
{
	if (cmd_nbr == 1)
	{
		printf("exit\n");
		if (ft_strs_len(cmd_args) == 1)
			clear_minishell(data);
		else if (ft_strs_len(cmd_args) >= 2)
			get_exit_code(data, cmd_args);
	}
}

void	get_exit_code(t_data *data, char **cmd_args)
{
	char	*code;

	code = ft_itoa(ft_atoi(cmd_args[1]));
	if (!code)
		g_exit_code = print_err("minishell: malloc() failed: %s\n", errno);
	else if (!ft_strcmp(cmd_args[1], code) && ft_strs_len(cmd_args) == 2)
	{
		g_exit_code = ft_atoi(cmd_args[1]);
		free(code);
		clear_minishell(data);
	}
	else if (ft_strcmp(cmd_args[1], code))
	{
		g_exit_code = 255;
		printf("minishell: exit: %s: numeric argument required", cmd_args[1]);
		free(code);
		clear_minishell(data);
	}
	else
		g_exit_code = print_err("minishell: exit: too many arguments", 0);
	free(code);
}
