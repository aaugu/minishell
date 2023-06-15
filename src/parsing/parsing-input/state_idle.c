/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_idle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:25:13 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/15 10:42:18 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../../../includes/parsing_input_state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_idle(t_fsm *fsm, t_token **tokens, char c, int last_exit)
{
	if (c == '<' || c == '>' || c == '|')
		finish_add(fsm, tokens, c);
	if (c == '\'' || c == '\"')
		fsm->quotes = true;
	if (c == '<')
		change_state_and_type(fsm, less_than, redir_in);
	else if (c == '>')
		change_state_and_type(fsm, greater_than, redir_out);
	else if (c == '|')
		change_state_and_type(fsm, s_pipe, t_pipe);
	else if (c == '\'')
	{
		fsm->meta = false;
		change_state_quotes_true(fsm, quote_s, last_exit);
	}
	else if (c == '\"')
		change_state_quotes_true(fsm, quote_d, last_exit);
	else if (c == '\0')
		finish_stop(fsm, tokens, c);
	else if (c == ' ')
		finish_buf(fsm, tokens, c);
	else
		add_to_buf(fsm, c);
}
