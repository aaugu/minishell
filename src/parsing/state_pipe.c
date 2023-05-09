/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:42:25 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/09 13:19:11 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_pipe(char c, t_state_machine *sm, t_token *tokens)
{
	if (c == '<' || c == '>')
		finish_add(c, sm, tokens);
	if (c == ' ' || c == '\\' || c == '\'' || c == '\"')
		finish_buf(sm, &tokens);
	if (c == '<')
		sm->current_state = less_than;
	else if (c == '>')
		sm->current_state = greater_than;
	else if (c == '|')
		parsing_error(sm, &tokens, c);
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
