/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:16:13 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 15:11:25 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "parsing_meta_state_machine.h"
#include "libft.h"

t_meta	*create_node_meta(char *buffer, t_m_fsm *fsm);
t_meta	*lst_last_meta(t_meta *meta_strs);

/* Add char to current buffer */
void	add_to_buf_meta(t_m_fsm *fsm, char c)
{
	fsm->buf[fsm->buf_size] = c;
	fsm->buf_size++;
}

/* Finish buffer, create a node of meta list and set its content. Then reset
state machine */
void	finish_buf_meta(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	t_meta	*new_meta;
	t_meta	*last;

	if (fsm->buf_size != 0 || (c == '\0' && *meta_strs == NULL))
	{
		new_meta = create_node_meta(fsm->buf, fsm);
		if (!new_meta)
			parsing_error_meta(&(fsm->current_state));
		if (*meta_strs == NULL)
			*meta_strs = new_meta;
		else
		{
			last = lst_last_meta(*meta_strs);
			last->next = new_meta;
		}
		init_meta_state_machine(fsm);
	}
}

void	finish_state_meta(t_m_fsm *fsm, t_meta **meta_strs, int state, char c)
{
	finish_buf_meta(fsm, meta_strs, c);
	fsm->current_state = state;
}

/* Create a node of chained list (meta) */
t_meta	*create_node_meta(char *buffer, t_m_fsm *fsm)
{
	t_meta	*meta;

	meta = NULL;
	meta = (t_meta *)malloc(sizeof(t_meta));
	if (!meta)
	{
		parsing_error_meta(&(fsm->current_state));
		return (NULL);
	}
	meta->content = ft_strdup(buffer);
	if (!meta->content)
	{
		free(meta);
		parsing_error_meta(&(fsm->current_state));
		return (NULL);
	}
	meta->next = NULL;
	return (meta);
}

/* Get the last element of a chained list */
t_meta	*lst_last_meta(t_meta *meta_strs)
{
	while (meta_strs->next != NULL)
		meta_strs = meta_strs->next;
	return (meta_strs);
}
