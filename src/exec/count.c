/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:24:11 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/07 11:36:32 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_mark_count:
 *	compte le nombre de d'élément voulu dans la structure token.
 */
int	ft_mark_count(t_token *token, t_type type)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	if (tmp->type == t_pipe)
		tmp = tmp->next;
	while (tmp && tmp->type != t_pipe)
	{
		if (tmp->type == type)
			i += 1;
		tmp = tmp->next;
	}
	return (i);
}

/* ft_pipe_count:
 *	compte le nombre de pipe dans la structure token.
 */
int	ft_pipe_count(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == t_pipe)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

/* ft_cmd_count:
 *	compte le nombre de commande dans la structure token.
 */
int	ft_cmd_count(t_token *token)
{
	t_token	*tmp;
	int		cmd_nbr;

	tmp = token;
	cmd_nbr = 0;
	while (tmp)
	{
		if (tmp->type == command)
			cmd_nbr++;
		tmp = tmp->next;
	}
	return (cmd_nbr);
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
