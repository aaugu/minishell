/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:35:29 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/08 10:03:06 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing_meta.h"

/* ft_do_heredoc:
 *	Récupère l'input du heredoc
 *	Vérifie si l'input est le Limiter puis stop le heredoc dans ce cas.
 *	Expande les variables d'env si besoin (ainsi que $?)
 *	Écrie dans le pipe (servant de heredoc) l'input.
 *	
 */
static void	ft_do_heredoc(t_token *t, t_data *d, int i)
{
	while (1)
	{
		ft_sig_n_input(d);
		if (d->heredoc.str)
		{
			if (ft_strlen(d->heredoc.str) > 0)
			{
				if (ft_strncmp(d->heredoc.str, t->next->content,
						ft_strlen(t->next->content)) == 0
					&& ft_strlen(t->next->content)
					== ft_strlen(d->heredoc.str))
					break ;
				if (d->heredoc.flag_doc == 1
					&& i == d->heredoc.here_doc_nbr - 1)
				{	
					if (t->next->quotes == false)
						d->heredoc.str = parsing_meta(d->heredoc.str,
								d->envp, d->env_size);
					write(d->heredoc.here_docfd[1],
						d->heredoc.str, ft_strlen(d->heredoc.str));
					write(d->heredoc.here_docfd[1], "\n", 1);
				}
			}
		}
		else
			ft_exit_doc(t, d);
	}
	ft_exit_doc(t, d);
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
