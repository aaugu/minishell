/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:52:13 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/07 12:16:16 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_is_next_pipe:
 *	test si il reste des pipes dans les tokens suivant
 */
static int	ft_is_next_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != t_pipe)
		tmp = tmp->next;
	if (tmp && tmp->type == t_pipe)
		return (1);
	return (0);
}

/* ft_is_prev_pipe:
 *	test si il y a des pipe dans les tokens précédent
 */
int	ft_is_prev_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type != t_pipe)
		tmp = tmp->prev;
	if (tmp && tmp->type == t_pipe)
		return (1);
	return (0);
}

/* ft_pipe_child:
 *	redirige les entrée et sortie standare vers le fd adéquat. 
 */
void	ft_pipe_child(t_data *data, t_token *token)
{
	if (data->great_mark == 0 && ft_is_next_pipe(token) == 1)
	{
		if (dup2(data->fd_array[data->child * 2], STDOUT) == -1)
			ft_child_error(token, data, ERR_DUP2);
	}
	if (data->less_mark == 0 && data->heredoc.flag_doc == 0
		&& ft_is_prev_pipe(token) == 1)
	{
		if (dup2(data->fd_array[(data->child * 2) - 1], STDIN) == -1)
			ft_child_error(token, data, ERR_DUP2);
	}
}

/* ft_set_pipe:
 *	Génère tout les pipes demandé par l'input.
 */
int	*ft_set_pipe(t_data *data)
{
	int	*fd_array;
	int	pipe_fd[2];
	int	fd_index;
	int	index_cmd;

	index_cmd = 0;
	fd_index = 0;
	fd_array = malloc(sizeof(int *) * (data->pipe_nbr) * 2);
	if (!fd_array)
		return (NULL);
	while (index_cmd < data->pipe_nbr)
	{
		if (pipe(pipe_fd) == -1)
		{
			ft_too_much_pipe(fd_array, data->pipe_nbr);
			return (NULL);
		}
		fd_array[fd_index] = pipe_fd[1];
		fd_array[fd_index + 1] = pipe_fd[0];
		fd_index += 2;
		index_cmd++;
	}
	return (fd_array);
}

/* ft_pipe_doc:
 *	Génère un pipe qui servira de à l'écriture et la lecture du herecdoc.
 */
void	ft_pipe_doc(t_data *data)
{
	if (data->heredoc.flag_doc == 1)
	{
		if (pipe(data->heredoc.here_docfd) == -1)
		{
			write(2, "Pipe here doc error\n", 20);
			exit(EXIT_FAILURE);
		}
	}
}
