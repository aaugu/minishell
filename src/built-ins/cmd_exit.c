/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:02:15 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/16 10:13:25 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../includes/built_ins.h"
#include "../../includes/print_error.h"
#include "../../libft/libft.h"

void	get_exit_code(t_data *data);

/*
Exit in bash : The exit() function causes normal process termination and the
least significant byte of status (i.e., status & 0xFF) is returned to the parent,
here it is
 */
void	cmd_exit(t_data *data)
{
	if (data->cmd_nbr == 1)
	{
		printf("exit\n");
		if (ft_strs_len(data->cmd) == 1)
			clear_minishell(data, EXIT_SUCCESS);
		else if (ft_strs_len(data->cmd) >= 2)
			get_exit_code(data);
	}
}

/* Set exit code depending on number of arguments and if they are numerical*/
void	get_exit_code(t_data *data)
{
	char	*code;

	code = ft_itoa(ft_atoi(data->cmd[1]));
	if (!code)
	{
		data->exit_code = print_err("minishell: malloc() failed:", errno);
		clear_minishell(data, data->exit_code);
	}
	else if (!ft_strcmp(data->cmd[1], code) && ft_strs_len(data->cmd) == 2)
	{
		data->exit_code = ft_atoi(data->cmd[1]);
		free(code);
		clear_minishell(data, data->exit_code);
	}
	else if (ft_strcmp(data->cmd[1], code))
	{
		data->exit_code = 255;
		printf("minishell: exit: %s: numeric argument required\n", data->cmd[1]);
		free(code);
		clear_minishell(data, data->exit_code);
	}
	else
		data->exit_code = print_err("minishell: exit: too many arguments\n", 0);
	free(code);
}
