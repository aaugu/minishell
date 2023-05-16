/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:10:58 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/03 15:14:39 by lvogt            ###   ########.fr       */
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
	ft_free_list(token);
	clear_history();
}

void	ft_exit_doc(t_token *token, t_data *data)
{
	ft_free_child_doc(data, token);
	exit(EXIT_SUCCESS);
}