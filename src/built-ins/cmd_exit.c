/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:15 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/30 12:50:17 by aaugu            ###   ########.fr       */
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

void	cmd_exit(t_data *data, char **cmd_args, int cmd_nbr)
{
	char	*code;

	printf("exit\n");
	code = ft_itoa(ft_atoi(cmd_args[1]));
	if (!code)
		g_exit_code = print_err("minishell: malloc() failed: %s\n", errno);
	else if (ft_strs_len(cmd_args) == 1 && cmd_nbr == 1)
		clear_minishell(data);
	else if (ft_strs_len(cmd_args) >= 2 && cmd_nbr == 1)
	{
		if (!ft_strcmp(cmd_args[1], code) && ft_strs_len(cmd_args) == 2)
			g_exit_code = ft_atoi(cmd_args[1]);
		else if (ft_strcmp(cmd_args[1], code))
			printf("minishell: exit: %s: numeric argument required", \
			cmd_args[1]);
		else
			g_exit_code = print_err("minishell: exit: too many arguments", 0);
		if ((!ft_strcmp(cmd_args[1], code) && ft_strs_len(cmd_args) == 2) || \
		ft_strcmp(cmd_args[1], code))
		{
			free(code);
			clear_minishell(data);
		}
	}
	free(code);
}

void	blabla(t_data *data, char **cmd_args, int cmd_nbr)
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
		printf("minishell: exit: %s: numeric argument required", cmd_args[1]);
		g_exit_code = 255;
		free(code);
		clear_minishell(data);
	}
	else
		g_exit_code = print_err("minishell: exit: too many arguments", 0);
}
