/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:35:29 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/05 16:23:28 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing_meta_heredoc.h"

/* ft_do_heredoc:
 *	Récupère l'input du heredoc
 *	Vérifie si l'input est le Limiter puis stop le heredoc dans ce cas.
 *	Expande les variables d'env si besoin (ainsi que $?)
 *	Écrie dans le pipe (servant de heredoc) l'input.
 */
static void	ft_do_heredoc(t_token *tmp, t_data *d, int i)
{
	while (1)
	{
		ft_sig_n_input(d);
		if (d->heredoc.str)
		{
			if (ft_strlen(d->heredoc.str) > 0)
			{
				if (ft_strncmp(d->heredoc.str, tmp->next->content,
						ft_strlen(tmp->next->content)) == 0
					&& ft_strlen(tmp->next->content)
					== ft_strlen(d->heredoc.str))
					break ;
				if (d->heredoc.flag_doc == 1
					&& i == d->heredoc.here_doc_nbr - 1)
				{
					if (tmp->next->quotes == false)
						d->heredoc.str = parsing_meta(d->heredoc.str, d->envp, d->env_size);
					write(d->heredoc.here_docfd[1],
						d->heredoc.str, ft_strlen(d->heredoc.str));
					write(d->heredoc.here_docfd[1], "\n", 1);
				}
			}
		}
		else
			ft_exit_doc(tmp, d);
	}
	ft_exit_doc(tmp, d);
}

int	ft_is_doc_last(t_token *token)
{
	t_token	*tmp;
	int		type;

	tmp = token;
	if (tmp->type == t_pipe)
		tmp = tmp->next;
	type = -1;
	while (tmp && tmp->type != t_pipe)
	{
		if (tmp->type == redir_in || tmp->type == heredoc)
			type = tmp->type;
		tmp = tmp->next;
	}
	if (type == heredoc)
		return (1);
	return (0);
}
/* ft_heredoc_nbr:
 * Compte le nombre de heredoc dans l'input.
 */
int	ft_heredoc_nbr(t_token *t)
{
	t_token	*tmp;
	int		i;

	tmp = t;
	i = 0;
	if (tmp->type == t_pipe)
		tmp = tmp->next;
	while (tmp && tmp->type != t_pipe)
	{
		if (tmp->type == heredoc)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

/* ft_do_child_doc:
 *	Lance l'écriture du heredoc.
 */
static void	ft_do_child_doc(pid_t *p, int i, t_data *d, t_token *t)
{
	free(p);
	ft_do_heredoc(t, d, i);
}

/* ft_doc_parent_process:
 *	Attend la fin du process (heredoc).
 *	Récupère l'exit code.
 */
static void	ft_doc_parent_process(pid_t *p, int i, t_data *d)
{
	int	status;

	waitpid(p[i], &status, 0);
	if (WIFEXITED(status))
		d->exit_code = WEXITSTATUS(status);
}

/* ft_heredoc_child:
 *	Ouvre autant de Heredoc que necésssaire grâce au fork.
 *	Récupère l'input et l'exit code. Puis passe au heredoc suivant.
 */
static void	ft_heredoc_child(t_data *d, pid_t *p, t_token *tmp, pid_t *p2)
{
	int	i;

	i = 0;
	while (i < d->heredoc.here_doc_nbr)
	{
		while (tmp->type != heredoc)
			tmp = tmp->next;
		p[i] = fork();
		if (p[i] < 0)
			return ;
		if (p[i] == 0)
		{
			free(p2);
			ft_do_child_doc(p, i, d, tmp);
		}
		else if (p[i] > 0)
		{
			ft_doc_parent_process(p, i, d);
			tmp = tmp->next;
			i++;
		}
	}
}

/* ft_heredoc:
 *	Ouvre un pipe qui servira de heredoc.
 *	Lance autant de heredoc que nécessaire.
 */
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
