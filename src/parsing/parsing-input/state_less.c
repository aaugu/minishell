/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:31 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/20 11:22:09 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_input_state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_less_than(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(fsm, tokens, c);
	if (c == '<')
		state_type_add_buf(fsm, less_than_d, heredoc, c);
	else if (c == '>')
	{
		finish_add(fsm, tokens, c);
		change_state_and_type(fsm, greater_than, redir_out);
	}
	else if (c == '|')
		parsing_error(fsm, &c);
	else if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == ' ')
		fsm->current_state = idle;
	else if (c == '\0')
		parsing_error(fsm, "newline");
	else if (c == '$')
		finish_add_tmp_state(fsm, tokens, c, dollar_idle);
	else
		finish_add_state(fsm, tokens, c, idle);
}

void	state_less_than_d(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == ' ' || c == '\'' || c == '\"')
		finish_buf(fsm, tokens, c);
	if (c == '>' || c == '|')
		parsing_error(fsm, &c);
	else if (c == '<')
		parsing_error(fsm, "newline");
	else if (c == '\'')
		change_state_quotes(fsm, limiter_quotes_s);
	else if (c == '\"')
		change_state_quotes(fsm, limiter_quotes_d);
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
	else if (c == ' ')
		return ;
	else
		finish_add_state(fsm, tokens, c, limiter_no_quotes);
}
