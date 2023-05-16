/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:35:29 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/12 15:31:12 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_do_heredoc(t_token *tmp, t_data *data, int i)
{
	while (1)
	{
		ft_sig_n_input(data);
		if (data->heredoc.str)
		{
			if (ft_strlen(data->heredoc.str) > 0)
			{
				if (ft_strncmp(data->heredoc.str, tmp->next->str,
						ft_strlen(tmp->next->str)) == 0
					&& ft_strlen(tmp->next->str)
					== ft_strlen(data->heredoc.str))
					break ;
				if (data->heredoc.flag_doc == 1
					&& i == data->heredoc.here_doc_nbr - 1)
				{
					write(data->heredoc.here_docfd[1],
						data->heredoc.str, ft_strlen(data->heredoc.str));
					write(data->heredoc.here_docfd[1], "\n", 1);
				}
			}
		}
		else
			ft_exit_doc(tmp, data);
	}
	ft_exit_doc(tmp, data);
}

int	ft_is_doc_last(t_token *token)
{
	t_token	*tmp;
	int		type;

	tmp = token;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	type = -1;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == LESS || tmp->type == LESS_LESS)
			type = tmp->type;
		tmp = tmp->next;
	}
	if (type == LESS_LESS)
		return (1);
	return (0);
}

int	ft_heredoc_nbr(t_token *t)
{
	t_token	*tmp;
	int		i;

	tmp = t;
	i = 0;
	if (tmp->type == PIPE)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == LESS_LESS)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	ft_do_child_doc(pid_t *p, int i, t_data *d, t_token *t)
{
	free(p);
	ft_do_heredoc(t, d, i);
}

static void	ft_doc_parent_process(pid_t *p, int i, t_data *d)
{
	int	status;

	waitpid(p[i], &status, 0);
	if (WIFEXITED(status))
		d->exit_code = WEXITSTATUS(status);
}

static void	ft_heredoc_child(t_data *c, pid_t *p, t_token *tmp, pid_t *p2)
{
	int	i;

	i = 0;
	while (i < c->heredoc.here_doc_nbr)
	{
		while (tmp->type != LESS_LESS)
			tmp = tmp->next;
		p[i] = fork();
		if (p[i] < 0)
			return ;
		if (p[i] == 0)
		{
			free(p2);
			ft_do_child_doc(p, i, c, tmp);
		}
		else if (p[i] > 0)
		{
			ft_doc_parent_process(p, i, c);
			tmp = tmp->next;
			i++;
		}
	}
}

void	ft_heredoc(t_token *token, t_data *data, pid_t *pid2)
{
	t_token	*tmp;
	pid_t	*pid;

	tmp = token;
	if (data->heredoc.here_doc_nbr > 0)
	{
		ft_pipe_doc(data);
		pid = malloc(sizeof(int) * data->heredoc.here_doc_nbr);
		if (!pid)
			return ;
		ft_heredoc_child(data, pid, tmp, pid2);
		free(pid);
	}
}
