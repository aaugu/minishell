/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:24:11 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/17 14:39:54 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
