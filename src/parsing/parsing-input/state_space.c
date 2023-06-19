/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:02:32 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/20 00:21:48 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_input_state_machine.h"

void	state_spaces(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '\0')
		parsing_error(fsm, "newline");
	else if (c == ' ')
		return ;
	else if (fsm->type == limiter)
	{
		if (c == '<')
			parsing_error(fsm, c);
		else if (c == '>')
			parsing_error(fsm, c);
		else if (c == '|')
			parsing_error(fsm, c);
		else if (c == '\'')
			fsm->current_state = limiter_quotes_s;
		else if (c == '\"')
			fsm->current_state = limiter_quotes_d;
		else
			fsm->current_state = limiter_no_quotes;
	}
	else if (fsm->type == infile || fsm->type == outfile)
	{
		if (c == '|')
			parsing_error(fsm, c);
	}
	else if (fsm->type == command || fsm->type == option)
	{
		if (c == '|')
			parsing_error(fsm, c);
	}
	else if (c == '\'')
		fsm->current_state = quote_s;
	else if (c == '\"')
		fsm->current_state = quote_s;
	else
		finish_add_state(fsm, tokens, c, idle);
}
