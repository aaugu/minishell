/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:13 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 13:26:59 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_idle(t_sm *sm, t_token **tokens, char c)
{
	if (c == '<' || c == '>' || c == '|')
		finish_add(sm, tokens, c);
	if (c == '<')
		change_state_and_type(sm, less_than, redir_in, c);
	else if (c == '>')
	{
		change_state_and_type(sm, greater_than, redir_out, c);
	}
	else if (c == '-' && sm->buf_size == 0)
	{
		finish_add(sm, tokens, c);
		change_state_and_type(sm, minus, option, c);
	}
	else if (c == '|')
		change_state_and_type(sm, s_pipe, t_pipe, c);
	else if (c == '\'')
		change_state_and_type(sm, quote_s, -1, c);
	else if (c == '\"')
		change_state_and_type(sm, quote_d, -1, c);
	else if (c == '\0')
		finish_stop(sm, tokens, c);
	else if (c == ' ')
		finish_buf(sm, tokens, c);
	else
		add_to_buf(sm, c);
}
