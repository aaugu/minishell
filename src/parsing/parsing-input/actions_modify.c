/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_modify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:03:33 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 21:26:50 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "parsing_input_state_machine.h"
#include "libft.h"

/* Combination of change_state_and_type() and add_to_buf() */
void	state_type_add_buf(t_fsm *fsm, t_state state, t_type type, char c)
{
	add_to_buf(fsm, c);
	change_state_and_type(fsm, state, type);
}

/* Change state and add on-going type */
void	change_state_and_type(t_fsm *fsm, t_state state, t_type type)
{
	if (state)
		fsm->current_state = state;
	if (type)
		fsm->type = type;
}

/* Change state and set quotes as true */
void	change_state_quotes(t_fsm *fsm, t_state state)
{
	fsm->quotes = true;
	fsm->current_state = state;
}

/* Add char to current buffer */
void	add_to_buf(t_fsm *fsm, char c)
{
	fsm->buf[fsm->buf_size] = c;
	fsm->buf_size++;
}

/* Add char to temporary buffer (used after a $ is encountered until a
finishing char of interpretation) */
void	add_to_tmp_buf(t_fsm *fsm, char c)
{
	fsm->tmp[fsm->tmp_size] = c;
	fsm->tmp_size++;
}
