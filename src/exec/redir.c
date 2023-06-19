/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:12:45 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/07 11:12:45 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_less_child:
 *	Ouvre le fichier donné en in puis redirige stdin par son fd. 
 */
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

/* ft_great_child:
 *	Ouvre le fichier donné en out en append ou trunc.
 *	redirige stdout vers le fd du dernier fichier out.
 */
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

/* ft_less_n_great:
 *	Gère l'ouverture et les redirections pour redir_out, redir_out_ap et redir_in
 */
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

/* ft_redirection:
 *	Compte le nombre de redirection (in/out/out + append)
 *	puis ferme ce qui n'est plus utile.
 */
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
