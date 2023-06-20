/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:10:58 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/20 10:19:13 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		exit(127);
	}
	else if (flag == ERR_OPEN_LESS || flag == ERR_OPEN_GREAT
		|| flag == ERR_DUP2)
		ft_fd_error(token, d, flag);
	else if (flag == ERR_PID)
		return ;
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
