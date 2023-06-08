/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:10:58 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/08 10:10:43 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_free_child_doc:
 *	free tout ce qu'il faut 
 */
void	ft_free_child_doc(t_data *data, t_token *token)
{
	if (data->heredoc.flag_doc == 1)
	{
		close(data->heredoc.here_docfd[0]);
		close(data->heredoc.here_docfd[1]);
	}
	ft_free_double(data->envp);
	if (data->all_path)
		ft_free_double(data->all_path);
	if (data->pipe_nbr > 0)
		ft_close_fd(data->fd_array, data->pipe_nbr);
	if (data->fd_array)
		free(data->fd_array);
	while (token && token->prev)
		token = token->prev;
	clear_tokens(&token);
	clear_history();
}

/* ft_exit_doc:
 *	free tout ce qu'il faut puis exit (0)
 */
void	ft_exit_doc(t_token *token, t_data *data)
{
	ft_free_child_doc(data, token);
	exit(EXIT_SUCCESS);
}

/* ft_cmd_error:
 *	Ecrit un message dans la sortie erreur pour un  command not found.
 */
void	ft_cmd_error(t_data *data)
{
	write(2, "minishell: ", 11);
	if (!data->cmd[0])
		write(2, " ", 1);
	else
		write(2, data->cmd[0], ft_strlen(data->cmd[0]));
	write(2, ": command not found\n", 20);
}

/* ft_fd_error:
 *	Ecrit les messages d'erreur pour les cas :
 *	ERR_OPEN_LESS, ERR_OPEN_GREAT ou ERR_DUP2
 */
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
		exit(1);
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

/* ft_child_error
 *	Gère les erreurs dans different cas.
 *	Pour ERR_EXECVE, ERR_OPEN_LESS, ERR_OPEN_GREAT, ERR_DUP2 ou ERR_PID
 */
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

/* ft_too_much_pipe:
 *	Ecrit un message d'erreur si la limit d'ouverture de pipe est atteinte 
 */
void	ft_too_much_pipe(int *fd_array, int pipe_nbr)
{
	write(2, "Minishell: pipe: environment limit.", 35);
	write(2, " Use a better terminal or use less pipe.\n", 41);
	if (fd_array)
		ft_close_fd(fd_array, pipe_nbr);
	if (fd_array)
		free(fd_array);
}
