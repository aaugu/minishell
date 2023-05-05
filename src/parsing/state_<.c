/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_<.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:31 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/05 16:20:46 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_less_than(char c, t_state_machine *sm, t_token *tokens)
{
	if (c == '>' || c == '|')
		finish_add(c, sm, tokens);
	if (c == ' ' || c == '\\' | c == '\'' || c == '\"')
		finish_buff(c, sm, tokens);
	if (c == '<')
	{
		add_to_buf(c, sm, tokens);
		sm->current_state = less_than_d;
	}
	else if (c == '>')
		sm->current_state = greater_than;
	else if (c == '|')
		sm->current_state = pipe;
	else if (c == '\\')
		sm->current_state = backslash;
	else if (c == '\'')
		sm->current_state = quote_s;
	else if (c == '\"')
		sm->current_state = quote_d;
	else if (c == '\0')
		finish_stop(sm, tokens);
	else if (c == ' ')
		sm->current_state = idle;
	else
		finish_add_idle(c, sm, tokens);
}

void	state_less_than_d(char c, t_state_machine *sm, t_token *tokens)
{
	if (c == '>' || c == '|')
		finish_add(c, sm, tokens);
	if (c == ' ' || c == '\\' | c == '\'' || c == '\"')
		finish_buff(c, sm, tokens);
	if (c == '<')
		sm->current_state = error;
	else if (c == '>')
		sm->current_state = greater_than;
	else if (c == '|')
		sm->current_state = pipe;
	else if (c == '\\')
		sm->current_state = backslash;
	else if (c == '\'')
		sm->current_state = quote_s;
	else if (c == '\"')
		sm->current_state = quote_d;
	else if (c == '\0')
		finish_stop(sm, tokens);
	else if (c == ' ')
		sm->current_state = idle;
	else
		finish_add_idle(c, sm, tokens);
}
