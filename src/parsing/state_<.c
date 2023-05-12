/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_<.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:31 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/12 13:31:56 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_less_than(char c, t_sm *sm, t_token **tokens)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(sm, tokens);
	if (c == '|')
		parsing_error(sm, tokens, &c);
	else if (c == '\0' || c == '>')
		parsing_error(sm, tokens, "newline");
	else if (c == '<')
	{
		add_to_buf(c, sm);
		sm->current_state = less_than_d;
	}
	else if (c == ' ')
		return ;
	else if (c == '\'')
		sm->current_state = quote_s;
	else if (c == '\"')
		sm->current_state = quote_d;
	else
		finish_add_idle(c, sm, tokens);
}

void	state_less_than_d(char c, t_sm *sm, t_token **tokens)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(sm, tokens);
	if (c == '<' || c == '>' || c == '|')
		parsing_error(sm, tokens, &c);
	else if (c == '\'')
		sm->current_state = quote_s;
	else if (c == '\"')
		sm->current_state = quote_d;
	else if (c == '\0')
		finish_stop(sm, tokens);
	else if (c == ' ')
		return ;
	else
		finish_add_idle(c, sm, tokens);
}
