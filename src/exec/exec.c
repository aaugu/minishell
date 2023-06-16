/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:15:04 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/16 10:47:55 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_exec_command:
 *	Regarde la présence et le nombre de heredoc.
 *	Si la derniere redirection est un heredoc.
 *	Regarde la présence de builtins et le definit si besoin.
 *	Lance la creation des Heredoc.
 *	Puis lance le child process pour executer pipe, builtin et commande.
 */
static void	ft_exec_command(t_token *t, t_data *d, pid_t *pid)
{
	t_token	*tmp;

	tmp = t;
	while (tmp)
	{	
		d->heredoc.ctrlc = 0;
		d->heredoc.here_doc_nbr = ft_heredoc_nbr(tmp);
		d->heredoc.flag_doc = ft_is_doc_last(tmp);
		if (d->child == 0 || tmp->type == t_pipe)
		{
			d->is_builtin = ft_is_builtins(tmp);
			ft_heredoc(tmp, d, pid);
			if (d->heredoc.ctrlc == 0)
				ft_process_child(d, tmp, pid);
			if (d->heredoc.flag_doc == 1)
			{
				close(d->heredoc.here_docfd[1]);
				close(d->heredoc.here_docfd[0]);
			}
			d->child++;
		}
		tmp = tmp->next;
	}
}

/* ft_wait:
 *	Attend la fin de chaque process et enregistre le dernier exit_code.
 */
void	ft_wait(pid_t *pid, t_data *data)
{
	pid_t	wpid;
	int		i;
	int		status;

	i = 0;
	while (i < data->pipe_nbr + 1)
	{
		wpid = waitpid(pid[i], &status, 0);
		if (WIFEXITED(status) && g_exit_code == 0 && data->exit_code == 0)
			data->exit_code = WEXITSTATUS(status);
		i++;
	}
}

/* ft_command:
 *	Si besoin créé les pipe et stock le FD dans un tableau.
 *	Lance l'execution des commands.
 *	Attend la fin de chaque process. 
 */
static void	ft_command(t_token *token, t_data *data)
{
	pid_t	*pid;

	data->fd_array = NULL;
	pid = (pid_t *)malloc(sizeof(pid_t) * (data->pipe_nbr + 1));
	if (!pid)
		return ;
	if (data->pipe_nbr > 0)
		data->fd_array = ft_set_pipe(data);
	if (data->fd_array == NULL && data->pipe_nbr > 0)
	{
		free(pid);
		return ;
	}
	ft_exec_command(token, data, pid);
	if (data->pipe_nbr > 0)
		ft_close_fd(data->fd_array, data->pipe_nbr);
	ft_wait(pid, data);
	free(pid);
	if (data->fd_array != NULL)
	{
		free(data->fd_array);
		data->fd_array = NULL;
	}
}

/* ft_check_pwd:
 *	Vérifie le chemin d'accès absolu du répertoire de travail courant.
 *	Si il n'est pas présent change le répertoire de travail courant vers la Trash.
 */
void	ft_check_pwd(t_data *data)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		if (chdir(data->trash_path) == -1)
			return ;
	}
	else
		return ;
}

/* ft_executor:
 *	Reçois le User-Input parsé sour la forme d'une structure token. 
 *	Compte le nombre de pipe ainsi que de commande.
 *	Puis ràz la cmd_path et le child.
 *	Lance l'execution de la commande puis check le PWD.
 *	Passe sur la trash si besoin.
 */
void	ft_executor(t_token *token, t_data *data)
{
	data->pipe_nbr = ft_pipe_count(token);
	data->cmd_nbr = ft_cmd_count(token);
	data->all_path = ft_find_path(data);
	data->cmd_path = NULL;
	data->child = 0;
	ft_command(token, data);
	ft_check_pwd(data);
	ft_free_double(data->all_path);
	data->all_path = NULL;
	ft_free_double(data->cmd);
	data->cmd = NULL;
}
