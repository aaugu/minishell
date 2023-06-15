/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:31:41 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/15 15:51:28 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing_meta_heredoc.h"

/* ft_free_child_doc:
 *	free tout ce qu'il faut 
 */
void	ft_free_child_doc(t_data *data, t_token *token)
{
	close(data->heredoc.here_docfd[0]);
	close(data->heredoc.here_docfd[1]);
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
	rl_clear_history();
}

/* ft_exit_doc:
 *	free tout ce qu'il faut puis exit (0)
 */
void	ft_exit_doc(t_token *token, t_data *data)
{
	ft_free_child_doc(data, token);
	exit(EXIT_SUCCESS);
}

void	ft_write_in_doc(t_token *t, t_data *d)
{
	if (t->next->quotes == false)
		d->heredoc.str = parsing_heredoc(d->heredoc.str, d->envp,
				d->env_size, d->exit_code);
	write(d->heredoc.here_docfd[1], d->heredoc.str, ft_strlen(d->heredoc.str));
	write(d->heredoc.here_docfd[1], "\n", 1);
	free(d->heredoc.str);
}

/* ft_sig_n_input:
 *	Écoute la présence d'un signal d'interruption
 *	Save l'input dans data->heredoc.str.
 */
void	ft_sig_n_input(t_data *data)
{
	set_signals_interactive_hd();
	data->heredoc.str = readline(">");
	set_signals_noninteractive();
}
