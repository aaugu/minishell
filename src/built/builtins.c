/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:01:39 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/17 13:36:37 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_which_builtins_child(t_data *data, t_token *token)
{
	int	exit_code;

	if (data->is_builtin == 3)
		ft_exit(data, token, NULL);
	else if (data->is_builtin == 4 && !data->cmd[1])
		ft_export(data);
	else if (data->is_builtin == 5)
		ft_pwd();
	else if (data->is_builtin == 6)
		ft_env(data);
	else if (data->is_builtin == 7)
		ft_echo(data);
	if (data->is_builtin == 3)
	{
		exit_code = data->exit_code;
		ft_free_child(token, data);
		exit(exit_code);
	}
	else
	{
		ft_free_child(token, data);
		exit(EXIT_SUCCESS);
	}
}

void	ft_which_builtins(t_data *data, t_token *token, pid_t *pid)
{
	int	error;

	error = 0;
	if (data->is_builtin == 1)
		error = ft_unset(data);
	else if (data->is_builtin == 2)
		error = ft_cd(data);
	else if (data->is_builtin == 3)
		ft_exit(data, token, pid);
	else if (data->is_builtin == 4)
		error = ft_export(data);
	data->exit_code = error;
}


int	ft_is_builtins(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && tmp->type == PIPE)
		tmp = tmp->next;
	while ((tmp && tmp->type != cmd) && (tmp && tmp->type != PIPE))
		tmp = tmp->next;
	if (tmp && tmp->str && tmp->type == CMD)
	{
		if (ft_strcmp_caps((tmp->str), "unset", 5) == 0 && len(tmp) == 5)
			return (1);
		else if (ft_strcmp_caps((tmp->str), "cd", 2) == 0 && len(tmp) == 2)
			return (2);
		else if (ft_strcmp_caps((tmp->str), "exit", 4) == 0 && len(tmp) == 4)
			return (3);
		else if (ft_strcmp_caps((tmp->str), "export", 6) == 0 && len(tmp) == 6)
			return (4);
		if (ft_strcmp_caps((tmp->str), "pwd", 3) == 0 && len(tmp) == 3)
			return (5);
		else if (ft_strcmp_caps((tmp->str), "env", 3) == 0 && len(tmp) == 3)
			return (6);
		else if (ft_strcmp_caps((tmp->str), "echo", 4) == 0 && len(tmp) == 4)
			return (7);
	}
	return (-1);
}
