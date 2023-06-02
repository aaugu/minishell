/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:01:39 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/02 10:30:04 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/built-ins.h"

void	ft_which_builtins_child(t_data *data)
{
	if (data->is_builtin == 4 && !data->cmd[1])
		ft_export(data);
	else if (data->is_builtin == 5)
		ft_pwd();
	else if (data->is_builtin == 6)
		cmd_env(data->envp, data->env_size, data->cmd);
	else if (data->is_builtin == 7)
		ft_echo(data);
}

/* ft_which_builtins:
 *	Lance le bultin unset, cd, exit ou export.
 */
void	ft_which_builtins(t_data *data, t_token *token, pid_t *pid)
{
	t_token	*tmp;
	pid_t *pid2;
	int	error;

	tmp = token;
	pid2 = pid;
	error = 0;
	if (data->is_builtin == 1)
		cmd_unset(data);
	else if (data->is_builtin == 2)
		error = ft_cd(data);
	else if (data->is_builtin == 3)
		cmd_exit(data);
	else if (data->is_builtin == 4)
		error = ft_export(data);
	data->exit_code = error;
}

int	ft_len(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp->content[i] && tmp->content[i] != ' ')
		i++;
	return (i);
}


int	ft_is_builtins(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && tmp->type == t_pipe)
		tmp = tmp->next;
	while ((tmp && tmp->type != command) && (tmp && tmp->type != t_pipe))
		tmp = tmp->next;
	if (tmp && tmp->content && tmp->type == command)
	{
		if (ft_strcmp_caps((tmp->content), "unset", 5) == 0 && ft_len(tmp) == 5)
			return (1);
		else if (ft_strcmp_caps((tmp->content), "cd", 2) == 0 && ft_len(tmp) == 2)
			return (2);
		else if (ft_strcmp_caps((tmp->content), "exit", 4) == 0 && ft_len(tmp) == 4)
			return (3);
		else if (ft_strcmp_caps((tmp->content), "export", 6) == 0 && ft_len(tmp) == 6)
			return (4);
		if (ft_strcmp_caps((tmp->content), "pwd", 3) == 0 && ft_len(tmp) == 3)
			return (5);
		else if (ft_strcmp_caps((tmp->content), "env", 3) == 0 && ft_len(tmp) == 3)
			return (6);
		else if (ft_strcmp_caps((tmp->content), "echo", 4) == 0 && ft_len(tmp) == 4)
			return (7);
	}
	return (-1);
}
