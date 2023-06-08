/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:03:10 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/07 12:10:56 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
void	ft_builtins_or_cmd(t_data *d, t_token *tmp, pid_t *pid)
{
	if (d->is_builtin > 0 && d->is_builtin < 5)
	{
		if (d->cmd_nbr == 1 || d->is_builtin == 1
			|| d->is_builtin == 2 || (d->is_builtin == 4 && d->cmd[1]))
			ft_which_builtins(d, tmp, pid);
	}
	else if (d->cmd && d->is_builtin < 0)
	{
		if (d->all_path || ft_strncmp(d->cmd[0], "/", 1) == 0)
			d->cmd_path = find_cmd_path(d);
	}
}

/* ft_full_str:
 *	Join la commande avec ses options séparé par un espace. 
 */
char	*ft_full_str(t_token *token)
{
	t_token	*tmp;
	char	*str;
	char	*tmp2;

	tmp = token;
	str = ft_strdup(tmp->content);
	while (tmp->next && tmp->next->type == option)
	{
		tmp = tmp->next;
		tmp2 = ft_strjoin(str, " ");
		free(str);
		str = ft_strjoin(tmp2, tmp->content);
		free(tmp2);
	}
	if (str)
		return (str);
	return (NULL);
}

/* ft_find_cmd:
 *	Recherche une commande et ses options pour les returnes
 *	sous la forme d'un tableau de char.
 */
char	**ft_find_cmd(t_token *token)
{
	t_token	*tmp;
	char	**cmd;
	char	*str;

	tmp = token;
	if (tmp && tmp->type == t_pipe)
		tmp = tmp->next;
	while (tmp && tmp->type != t_pipe && tmp->type != command)
		tmp = tmp->next;
	if (tmp && tmp->type == command)
	{
		str = ft_full_str(tmp);
		cmd = ft_split(str, ' ');
		free(str);
		if (cmd)
			return (cmd);
	}
	return (NULL);
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
