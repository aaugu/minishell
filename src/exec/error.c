/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:10:58 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/17 12:29:55 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	clear_tokens(token);
	clear_history();
}

void	ft_exit_doc(t_token *token, t_data *data)
{
	ft_free_child_doc(data, token);
	exit(EXIT_SUCCESS);
}

void	ft_cmd_error(t_data *data)
{
	write(2, "minishell: ", 11);
	if (!data->cmd[0])
		write(2, " ", 1);
	else
		write(2, data->cmd[0], ft_strlen(data->cmd[0]));
	write(2, ": command not found\n", 20);
}
