/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:50:08 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/31 14:20:16 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_exec_cmd:
 *	Ne fait rien dans les cas des builtin unset et cd ou exit sans option.
 *	
 */
void	ft_exec_cmd(t_token *tmp, t_data *data)
{
	if ((data->is_builtin > 0 && data->is_builtin < 3)
		|| (data->is_builtin == 3 && !data->cmd[1]))
		return ;
	while (tmp->type != command)
		tmp = tmp->next;
	if (data->is_builtin > 3 || (data->is_builtin == 3 && data->cmd[1]))
		ft_which_builtins_child(data);
	else if (!data->cmd_path)
	{
		ft_cmd_error(data);
		ft_free_child(tmp, data);
		exit(5);
	}
	else if (data->cmd_path)
	{
		execve(data->cmd_path, data->cmd, data->envp);
		ft_child_error(tmp, data, ERR_EXECVE);
	}
}

void	ft_fd_error(t_token *token, t_data *d, int flag)
{
	if (flag == ERR_OPEN_LESS)
	{
		if (ft_strlen(token->next->content) != 0)
		{
			write(2, "minishell: ", 11);
			write(2, token->next->content, ft_strlen(token->next->content));
			write(2, ": No such file or directory\n", 28);
		}
		ft_free_child(token, d);
		exit(4);
	}
	else if (flag == ERR_OPEN_GREAT)
	{
		if (ft_strlen(token->next->content) != 0)
		{
			write(2, token->next->content, ft_strlen(token->next->content));
			write(2, ": Permission denied\n", 20);
		}
		ft_free_child(token, d);
		exit(4);
	}
	else if (flag == ERR_DUP2)
	{
		write(2, "Dup2, error\n", 12);
		ft_free_child(token, d);
		exit(EXIT_SUCCESS);
	}
}

void	ft_free_child(t_token *token, t_data *d)
{
	if (d->heredoc.flag_doc == 1)
	{
		close(d->heredoc.here_docfd[0]);
		close(d->heredoc.here_docfd[1]);
	}
	if (d->all_path)
		ft_free_double(d->all_path);
	if (d->cmd)
		ft_free_double(d->cmd);
	if (d->cmd_path && d->is_builtin < 0)
		free(d->cmd_path);
	if (d->pipe_nbr > 0)
		ft_close_fd(d->fd_array, d->pipe_nbr);
	if (d->fd_array)
		free(d->fd_array);
	ft_free_double(d->envp);
	while (token && token->prev)
		token = token->prev;
	clear_tokens(&token);
	rl_clear_history();
	free(d->user_input);
}


void	ft_child_error(t_token *token, t_data *d, int flag)
{
	if (flag == ERR_EXECVE)
	{
		write(2, "minishell: ", 11);
		write(2, d->cmd[0], ft_strlen(d->cmd[0]));
		write(2, ": command not found\n", 20);
		ft_free_child(token, d);
		exit(5);
	}
	else if (flag == ERR_OPEN_LESS || flag == ERR_OPEN_GREAT
		|| flag == ERR_DUP2)
		ft_fd_error(token, d, flag);
	else if (flag == ERR_PID)
		;
}

void	ft_less_child(t_data *d, t_token *tmp, int less)
{
	int		fd;

	fd = -1;
	if (tmp->type == redir_in)
	{
		fd = open(tmp->next->content, O_RDONLY);
		if (fd == -1)
			ft_child_error(tmp, d, ERR_OPEN_LESS);
		if (less == d->less_mark)
		{
			if (dup2(fd, STDIN) == -1)
			{
				close(fd);
				ft_child_error(tmp, d, ERR_DUP2);
			}
		}
		close(fd);
	}
}

void	ft_great_child(t_data *d, t_token *token, int great)
{
	int		fd;

	fd = -1;
	if (token->type == redir_out_ap)
		fd = open(token->next->content, O_WRONLY | O_APPEND | O_CREAT, 0640);
	else if (token->type == redir_out)
		fd = open(token->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0640);
	if (fd == -1)
		ft_child_error(token, d, ERR_OPEN_GREAT);
	if (great == d->great_mark)
	{
		if (dup2(fd, STDOUT) == -1)
		{
			close(fd);
			ft_child_error(token, d, ERR_DUP2);
		}
	}
	close(fd);
}

void	ft_less_n_great(t_data *data, t_token *tmp)
{
	t_token	*tmp2;
	int		great;
	int		less;

	tmp2 = tmp;
	great = 0;
	less = 0;
	while (tmp2 && tmp2->type != t_pipe)
	{
		if (tmp2->type == redir_out || tmp2->type == redir_out_ap)
		{
			great++;
			ft_great_child(data, tmp2, great);
		}
		else if (tmp2->type == redir_in)
		{
			less++;
			ft_less_child(data, tmp2, less);
		}
		tmp2 = tmp2->next;
	}
}

void	ft_redirection(t_token *tmp, t_data *data)
{
	data->great_mark = ft_mark_count(tmp, redir_out);
	data->great_mark += ft_mark_count(tmp, redir_out_ap);
	data->less_mark = ft_mark_count(tmp, redir_in);
	if (data->less_mark > 0 || data->great_mark > 0)
		ft_less_n_great(data, tmp);
	if (data->heredoc.flag_doc == 1)
	{
		if (dup2(data->heredoc.here_docfd[0], STDIN) == -1)
		{
			close(data->heredoc.here_docfd[0]);
			close(data->heredoc.here_docfd[1]);
			write(2, "Error dup2 here_doc\n", 22);
		}
		close(data->heredoc.here_docfd[0]);
		close(data->heredoc.here_docfd[1]);
	}
	ft_pipe_child(data, tmp);
}

/* ft_exec_child:
 *	Setup les redirections
 *	Ferme les FD si pipe_nbr > 0
 *	Execute la commande
 */
void	ft_exec_child(t_data *data, t_token *tmp)
{
	t_token	*tmp2;

	tmp2 = tmp;
	if (tmp2->type == t_pipe)
		tmp2 = tmp2->next;
	ft_redirection(tmp2, data);
	if (data->pipe_nbr > 0)
		ft_close_fd(data->fd_array, data->pipe_nbr);
	if (ft_is_cmd(tmp) == 1)
		ft_exec_cmd(tmp2, data);
	ft_free_child(tmp2, data);
	exit(EXIT_SUCCESS);
}

/* ft_process_child:
 *	Cherche la commande, lance le builtin adéquat si besoin.
 *	
 */
void	ft_process_child(t_data *d, t_token *tmp, pid_t *p)
{
	d->cmd = ft_find_cmd(tmp);
	ft_builtins_or_cmd(d, tmp, p);
	p[d->child] = fork();
	if (p[d->child] < 0)
		return ;
	else if (p[d->child] == 0)
	{
		if (p)
			free(p);
		ft_exec_child(d, tmp);
		exit(EXIT_SUCCESS);
	}
	if (d->cmd && d->is_builtin < 0)
		free(d->cmd_path);
	d->cmd_path = NULL;
	if (d->cmd)
	{
		ft_free_double(d->cmd);
		d->cmd = NULL;
	}
}
