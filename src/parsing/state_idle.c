/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:13 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 09:53:48 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_idle(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	if (c == '<')
		change_state_and_type(fsm, less_than, redir_in, c);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out, c);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe, c);
	else if (c == '\'')
		fsm->current_state = quote_s;
	else if (c == '\"')
		fsm->current_state = quote_d;
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
	else if (c == ' ')
		finish_buf(fsm, tokens, c);
	else
		add_to_buf(fsm, c);
}
