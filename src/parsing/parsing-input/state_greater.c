/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_greater.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:53:20 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/20 00:28:49 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "parsing_input_state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_greater_than(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(fsm, tokens, c);
	if (c == '<')
		parsing_error(fsm, &c);
	else if (c == '>')
		state_type_add_buf(fsm, greater_than_d, redir_out_ap, c);
	else if (c == '|')
		parsing_error(fsm, "newline");
	else if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == ' ')
		fsm->current_state = space;
	else if (c == '\0')
		parsing_error(fsm, "newline");
	else if (c == '$')
		finish_add_tmp_state(fsm, tokens, c, dollar_idle);
	else
		finish_add_state(fsm, tokens, c, idle);
}

/* Will set current state according to char and decide which action to perform
if needed */
void	state_greater_than_d(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(fsm, tokens, c);
	if (c == '>' || c == '<' || c == '|')
		parsing_error(fsm, &c);
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
	else if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == ' ')
		fsm->current_state = space;
	else if (c == '$')
		finish_add_tmp_state(fsm, tokens, c, dollar_idle);
	else
		finish_add_state(fsm, tokens, c, idle);
}
