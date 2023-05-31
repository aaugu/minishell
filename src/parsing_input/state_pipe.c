/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:42:25 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 14:16:25 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing_input_state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_pipe(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(fsm, tokens, c);
	if (c == '<' || c == '>')
		finish_add(fsm, tokens, c);
	if (c == '<')
		fsm->current_state = less_than;
	else if (c == '>')
		fsm->current_state = greater_than;
	else if (c == '|')
		parsing_error(fsm, &c);
	else if (c == '\'')
		fsm->current_state = quote_s;
	else if (c == '\"')
		fsm->current_state = quote_d;
	else if (c == ' ')
		fsm->current_state = idle;
	else if (c == '\0')
		parsing_error(fsm, "newline");
	else
		finish_add_idle(fsm, tokens, c);
}
