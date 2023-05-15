/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_>.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:53:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 15:45:25 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"
#include "../../includes/parsing.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_greater_than(t_sm *sm, t_token **tokens, char c)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(sm, tokens, c);
	if (c == '<')
		parsing_error(sm, tokens, &c);
	else if (c == '>')
		state_type_add_buf(sm, greater_than_d, redir_out_ap, c);
	else if (c == '|')
		return ;
	else if (c == '\'')
		sm->current_state = quote_s;
	else if (c == '\"')
		sm->current_state = quote_d;
	else if (c == ' ')
		sm->current_state = idle;
	else if (c == '\0')
		parsing_error(sm, tokens, "newline");
	else
		finish_add_idle(sm, tokens, c);
}

/* Will set current state according to char and decide which action to perform
if needed */
void	state_greater_than_d(t_sm *sm, t_token **tokens, char c)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(sm, tokens, c);
	if (c == '>' || c == '<' || c == '|')
		parsing_error(sm, tokens, &c);
	else if (c == '\'')
		sm->current_state = quote_s;
	else if (c == '\"')
		sm->current_state = quote_d;
	else if (c == '\0')
		finish_stop(sm, tokens, c);
	else if (c == ' ')
		sm->current_state = idle;
	else
		finish_add_idle(sm, tokens, c);
}
