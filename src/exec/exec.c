/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:15:04 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/12 15:02:56 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exec_command(t_token *t, t_data *d, pid_t *pid)
{
	t_token	*tmp;

	tmp = t;
	while (tmp)
	{
		d->heredoc.here_doc_nbr = ft_heredoc_nbr(tmp);
		d->heredoc.flag_doc = ft_is_doc_last(tmp);
		if (d->child == 0 || tmp->type == PIPE)
		{
			d->is_builtin = ft_is_builtins(tmp);
			ft_heredoc(tmp, d, pid);
			ft_process_child(d, tmp, pid);
			if (d->heredoc.flag_doc == 1)
			{
				close(d->heredoc.here_docfd[1]);
				close(d->heredoc.here_docfd[0]);
			}
			d->child++;
		}
		tmp = tmp->next;
	}
}

void	ft_wait(pid_t *pid, t_data *data)
{
	pid_t	wpid;
	int		i;
	int		status;

	i = 0;
	while (i < data->pipe_nbr + 1)
	{
		wpid = waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		i++;
	}
}

static void	ft_command(t_token *token, t_data *data)
{
	pid_t	*pid;

	data->fd_array = NULL;
	pid = (pid_t *)malloc(sizeof(pid_t) * (data->pipe_nbr + 1));
	if (!pid)
		return ;
	if (data->pipe_nbr > 0)
		data->fd_array = ft_set_pipe(data);
	if (data->fd_array == NULL && data->pipe_nbr > 0)
	{
		free(pid);
		return ;
	}
	ft_exec_command(token, data, pid);
	if (data->pipe_nbr > 0)
		ft_close_fd(data->fd_array, data->pipe_nbr);
	ft_wait(pid, data);
	free(pid);
	if (data->fd_array != NULL)
		free(data->fd_array);
}

void	ft_check_pwd(t_data *data)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		if (chdir(data->trash_path) == -1)
			return ;
	}
	else
		return ;
}

void	ft_executor(t_token *token, t_data *data)
{
	data->pipe_nbr = ft_pipe_count(token);
	data->cmd_nbr = ft_cmd_count(token);
	data->all_path = ft_find_path(data);
	ft_command(token, data);
	ft_check_pwd(data);
}
