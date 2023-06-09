/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:13 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/20 13:17:19 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "parsing_input_state_machine.h"

void	change_state_dollar_idle(t_fsm *fsm, int state, int type, char c);

/* Will set current state according to char and decide which action to perform
if needed */
void	state_idle(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	if (c == '<')
		change_state_and_type(fsm, less_than, redir_in);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe);
	else if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
	else if (c == ' ' && *tokens == NULL && fsm->buf_size == 0)
		fsm->current_state = space;
	else if (c == ' ')
		finish_buf(fsm, tokens, c);
	else if (c == '$')
		change_state_dollar_idle(fsm, dollar_idle, fsm->type, c);
	else
		add_to_buf(fsm, c);
}

void	change_state_dollar_idle(t_fsm *fsm, int state, int type, char c)
{
	fsm->tmp[fsm->tmp_size] = c;
	fsm->tmp_size++;
	change_state_and_type(fsm, state, type);
}

void	state_space(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	if (c == ' ')
		return ;
	else if (c == '<')
		change_state_and_type(fsm, less_than, redir_in);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe);
	else if (c == '\'')
		change_state_quotes(fsm, quote_s);
	else if (c == '\"')
		change_state_quotes(fsm, quote_d);
	else if (c == '\0')
		fsm->current_state = error;
	else if (c == '$')
		change_state_dollar_idle(fsm, dollar_idle, fsm->type, c);
	else
		state_type_add_buf(fsm, idle, fsm->type, c);
}
