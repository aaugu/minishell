/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:13 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/05 14:22:38 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/state_machine.h"

void	from_idle(char c, t_state_machine *sm, t_token *tokens);

/* Will set current state according to char and add to/finish buffer if 
needed */
void	state_idle(char c, t_state_machine *sm, t_token *tokens)
{
	if (c == '<' || c == '>' | c == '|')
		from_idle(c, sm, tokens);
	if (c == '\\')
		sm->current_state = backslash;
	if (c == '\'')
		sm->current_state = quote_s;
	if (c == '\"')
		sm->current_state = quote_d;
	if (c == '\0')
	{
		finish_and_reset_buf(sm, tokens);
		sm->current_state = stop;
	}
	if (c == ' ')
		finish_and_reset_buf(sm, tokens);
	else
		add_to_buf(c, sm, tokens);
}

void	from_idle(char c, t_state_machine *sm, t_token *tokens)
{
	finish_and_reset_buf(sm, tokens);
	add_to_buf(c, sm, tokens);
	if (c == '<')
		sm->current_state = less_than;
	if (c == '>')
		sm->current_state = greater_than;
	if (c == '|')
		sm->current_state = pipe;
}
