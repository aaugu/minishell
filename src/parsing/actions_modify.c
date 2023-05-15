/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_modify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:03:33 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 11:31:18 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Add char to current buffer */
void	add_to_buf(t_sm *sm, char c)
{
	sm->buf[sm->buf_size] = c;
	sm->buf_size++;
}

/* Change state and add on-going type */
void	change_state_and_type(t_sm *sm, t_state state, t_type type, char c)
{
	if (state == idle && c == '\'')
		sm->meta = false;
	sm->current_state = state;
	if (type >= 0)
		sm->type = type;
}

/* Combination of change_state_and_type() and add_to_buf() */
void	state_type_add_buf(t_sm *sm, t_state state, t_type type, char c)
{
	change_state_and_type(sm, state, type, c);
	add_to_buf(sm, c);
}
