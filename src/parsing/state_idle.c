/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:13 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/11 14:24:00 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_idle(char c, t_state_machine *sm, t_token **tokens)
{
	if (c == '<' || c == '>' || c == '|')
		finish_add(c, sm, tokens);
	if (c == '<')
		sm->current_state = less_than;
	else if (c == '>')
		sm->current_state = greater_than;
	else if (c == '|')
		sm->current_state = pipes;
	else if (c == '\'')
		sm->current_state = quote_s;
	else if (c == '\"')
	{
		sm->quotes_d = true;
		sm->current_state = quote_d;
	}
	else if (c == '\0')
		finish_stop(sm, tokens);
	else if (c == ' ')
		finish_buf(sm, tokens);
	else
		add_to_buf(c, sm);
}
