/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:01:39 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/30 10:26:11 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_which_builtins_child(t_data *data, t_token *token)
{
	int	exit_code;

	if (data->is_builtin == 3)
		/*ft_exit(data, token, NULL);*/ printf("test exit 1\n");
	else if (data->is_builtin == 4 && !data->cmd[1])
		/*ft_export(data);*/ printf("test export 1\n");
	else if (data->is_builtin == 5)
		ft_pwd();
	else if (data->is_builtin == 6)
		/*ft_env(data);*/ printf("test env\n");
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
	t_token	*tmp;
	pid_t *pid2;
	int	error;

	tmp = token;
	pid2 = pid;
	error = 0;
	if (data->is_builtin == 1)
		/*error = ft_unset(data);*/ printf("test unset\n");
	else if (data->is_builtin == 2)
		error = ft_cd(data);
	else if (data->is_builtin == 3)
		/*ft_exit(data, token, pid);*/ printf("test exit 2\n");
	else if (data->is_builtin == 4)
		/*error = ft_export(data);*/ printf("test export 2\n");
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
