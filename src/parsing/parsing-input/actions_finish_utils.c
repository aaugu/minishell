/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_finish_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:30:15 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 14:50:34 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing_input_state_machine.h"

/* Combination of finish_buf() and add_to_buff() */
void	finish_add(t_fsm *fsm, t_token **tokens, char c)
{
	finish_buf(fsm, tokens, c);
	add_to_buf(fsm, c);
}

/* Combination of finish_buff() and set current state to stop */
void	finish_stop(t_fsm *fsm, t_token **tokens, char c)
{
	finish_buf(fsm, tokens, c);
	fsm->current_state = stop;
}

/* Combination of finish_add() and set current state to idle */
void	finish_add_state(t_fsm *fsm, t_token **tokens, char c, int state)
{
	finish_add(fsm, tokens, c);
	fsm->current_state = state;
}

void	finish_add_tmp_state(t_fsm *fsm, t_token **tokens, char c, int state)
{
	finish_buf(fsm, tokens, c);
	add_to_tmp_buf(fsm, c);
	fsm->current_state = state;
}
