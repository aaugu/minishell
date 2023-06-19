/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:03:10 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/19 19:30:40 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "print_error.h"

char	**fill_cmd_with_args(t_token *cmd, int size);

/* find_cmd_path:
 *	Regarde si la commande commence par "./"
 *	puis lance le programe dans minishell.
 *	Regarde si la commande commence par "/" puis verifie accesibilité.
 *	Sinon verifi pour chaque path l'accesibilité.
 *	Return : la chaine de caractère qui permet l'access de la commande.
 */
char	*find_cmd_path(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!data->cmd[0])
		return (NULL);
	if (ft_strncmp(data->cmd[0], "./", 2) == 0)
		return (ft_launcher(data));
	else if (ft_strncmp(data->cmd[0], "/", 1) == 0)
	{
		if (access(data->cmd[0], X_OK) == 0)
		{
			tmp = ft_strdup(data->cmd[0]);
			return (tmp);
		}
	}
	while (data->all_path[i])
	{
		tmp = ft_strjoin(data->all_path[i], data->cmd[0]);
		if (access(tmp, X_OK | F_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

/* ft_builtins_or_cmd:
 *	Si la commande n'est pas un builtin -> cherche la path de la commande.
 *	Si cmd_nbr est de 1 lance le builtin unset, cd, exit ou export.
 *	(donc pas de pipe)
 *	Si cmd_nbr est autre ne fait que unset, cd ou export.
 */
void	ft_builtins_or_cmd(t_data *d)
{
	if (d->is_builtin > 0 && d->is_builtin < 5)
	{
		if (d->cmd_nbr == 1 || d->is_builtin == 1
			|| d->is_builtin == 2 || (d->is_builtin == 4 && d->cmd[1]))
			ft_which_builtins(d);
	}
	else if (d->cmd && d->is_builtin < 0)
	{
		if (d->all_path || ft_strncmp(d->cmd[0], "/", 1) == 0)
			d->cmd_path = find_cmd_path(d);
	}
}

/* ft_find_cmd:
 *	Recherche une commande et ses options pour les returnes
 *	sous la forme d'un tableau de char.
 */
char	**ft_find_cmd(t_token *token, t_data *d)
{
	t_token	*tmp;
	t_token	*cmd;
	char	**cmd_args;
	int		size;

	cmd_args = NULL;
	tmp = token;
	if (tmp && tmp->type == t_pipe)
		tmp = tmp->next;
	while (tmp && tmp->type != t_pipe && tmp->type != command)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	cmd = tmp;
	tmp = tmp->next;
	size = 1;
	while (tmp && tmp->type == option)
	{
		size++;
		tmp = tmp->next;
	}
	cmd_args = fill_cmd_with_args(cmd, size);
	if (!cmd_args)
		exit_print_error(d, errno);
	return (cmd_args);
}

char	**fill_cmd_with_args(t_token *cmd, int size)
{
	char	**cmd_args;
	int		i;

	cmd_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cmd_args)
		return (NULL);
	cmd_args[size] = NULL;
	i = 0;
	while (i < size)
	{
		cmd_args[i] = ft_strdup(cmd->content);
		if (!cmd_args[i])
		{
			ft_strs_free(cmd_args, size);
			return (NULL);
		}
		i++;
		cmd = cmd->next;
	}
	return (cmd_args);
}

/* ft_is_cmd:
 *	Cherche si il il y a une commande à executer
 *	avant la présence d'un pipe ou la fin de l'input.
 */
int	ft_is_cmd(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == t_pipe)
		tmp = tmp->next;
	while (tmp && tmp->type != t_pipe)
	{
		if (tmp->type == command)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
