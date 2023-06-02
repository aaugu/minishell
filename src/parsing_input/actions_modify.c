/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_modify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:03:33 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/02 10:54:20 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../../includes/parsing_input_state_machine.h"

/* Add char to current buffer */
void	add_to_buf(t_fsm *fsm, char c)
{
	fsm->buf[fsm->buf_size] = c;
	fsm->buf_size++;
}

/* Change state and add on-going type */
void	change_state_and_type(t_fsm *fsm, t_state state, t_type type)
{
	if (state)
		fsm->current_state = state;
	if (type)
		fsm->type = type;
}

/* Combination of change_state_and_type() and add_to_buf() */
void	state_type_add_buf(t_fsm *fsm, t_state state, t_type type, char c)
{
	add_to_buf(fsm, c);
	change_state_and_type(fsm, state, type);
}

void	change_state_quotes_true(t_fsm *fsm, t_state state)
{
	fsm->current_state = state;
	fsm->quotes = true;
}
