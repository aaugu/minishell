/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:13 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/12 13:39:53 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_idle(char c, t_sm *sm, t_token **tokens)
{
	if (c == '<' || c == '>' || c == '|')
		finish_add(c, sm, tokens);
	if (c == '<')
		change_state_and_type(less_than, redir_in, sm);
	else if (c == '>')
		change_state_and_type(greater_than, redir_out, sm);
	else if (c == '|')
		change_state_and_type(pipes, t_pipe, sm);
	else if (c == '\'')
	{
		sm->meta = false;
		change_state_and_type(quote_s, undefined, sm);
	}
	else if (c == '\"')
		change_state_and_type(quote_d, undefined, sm);
	else if (c == '\0')
		finish_stop(sm, tokens);
	else if (c == ' ')
		finish_buf(sm, tokens);
	else if (c == '-' && sm->type == cmd)
		state_type_add_buf(minus, option, c, sm);
	else
	{
		get_type(sm);
		state_type_add_buf(idle, sm->type, c, sm);
	}
}
