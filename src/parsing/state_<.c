/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_<.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:31 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 13:59:29 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_less_than(t_sm *sm, t_token **tokens, char c)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(sm, tokens, c);
	if (c == '<')
		state_type_add_buf(sm, less_than_d, heredoc, c);
	else if (c == '>')
	{
		finish_add(sm, tokens, c);
		change_state_and_type(sm, greater_than, redir_out, c);
	}
	else if (c == '|')
		parsing_error(sm, tokens, &c);
	else if (c == '\'')
		sm->current_state = quote_s;
	else if (c == '\"')
		sm->current_state = quote_d;
	else if (c == ' ')
		return ;
	else if (c == '\0')
		parsing_error(sm, tokens, "newline");
	else
		finish_add_idle(sm, tokens, c);
}

void	state_less_than_d(t_sm *sm, t_token **tokens, char c)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(sm, tokens, c);
	if (c == '<' || c == '>' || c == '|')
		parsing_error(sm, tokens, &c);
	else if (c == '\'')
		sm->current_state = quote_s;
	else if (c == '\"')
		sm->current_state = quote_d;
	else if (c == '\0')
		finish_stop(sm, tokens, c);
	else if (c == ' ')
		return ;
	else
		finish_add_idle(sm, tokens, c);
}
