/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_modify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:03:33 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/12 11:43:27 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Add char to current buffer */
void	add_to_buf(char c, t_state_machine *sm)
{
	sm->buf[sm->buf_size] = c;
	sm->buf_size++;
}

/* Change state and add on going type */
void	change_state_and_type(t_state state, t_type type, t_state_machine *sm)
{
	sm->current_state = state;
	sm->type = type;
}

void	state_type_add_buf(t_state s, t_type t, char *c, t_state_machine *sm)
{
	change_state_and_type(s, t, sm);
	add_to_buf(c, sm);
}
