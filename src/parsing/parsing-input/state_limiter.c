/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_limiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:37:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 00:30:16 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_input_state_machine.h"

void	state_limiter_no_quotes(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '\0')
		finish_stop(fsm, tokens, c);
	if (c == '>' || c == '<' || c == '|' || c == ' ')
		finish_add(fsm, tokens, c);
	if (c == '<')
		change_state_and_type(fsm, less_than, redir_in);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe);
	else if (c == '\'')
		change_state_quotes(fsm, limiter_quotes_s);
	else if (c == '\"')
		change_state_quotes(fsm, limiter_quotes_d);
	else
		add_to_buf(fsm, c);
}

void	state_limiter_quotes_s(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '\0')
		parsing_error(fsm, "'");
	if (c == '\'')
	{
		finish_buf(fsm, tokens, c);
		fsm->current_state = limiter_no_quotes;
	}
	else
		add_to_buf(fsm, c);
}

void	state_limiter_quotes_d(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '\0')
		parsing_error(fsm, "\"");
	if (c == '\"')
	{
		finish_buf(fsm, tokens, c);
		fsm->current_state = limiter_no_quotes;
	}
	else
		add_to_buf(fsm, c);
}
