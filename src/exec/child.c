/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:50:08 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/12 11:14:47 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_exec_cmd:
 *	Ne fait rien dans les cas des builtin unset et cd ou exit sans option.
 *	Gère export sans option, pwd, env et echo.
 *	vérifie la présence de cmd path
 *	execute avec execve la commande.
 */
void	ft_exec_cmd(t_token *tmp, t_data *data)
{
	if ((data->is_builtin > 0 && data->is_builtin < 4))
		return ;
	while (tmp->type != command)
		tmp = tmp->next;
	if (data->is_builtin > 3)
		ft_which_builtins_child(data);
	else if (!data->cmd_path)
	{
		ft_cmd_error(data);
		ft_free_child(tmp, data);
		exit(127);
	}
	else if (data->cmd_path)
	{
		execve(data->cmd_path, data->cmd, data->envp);
		ft_child_error(tmp, data, ERR_EXECVE);
	}
}

/* ft_free_child:
 *	ferme l'entré sorti du heredoc
 *	free tout ce qui doit l'être.
 */
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

/* ft_exec_child:
 *	Setup les redirections
 *	Ferme les FD si pipe_nbr > 0
 *	Si il existe encore une commande, l'execute
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
 *	pour toute les autres commande, l'éxecute.
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
