/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:39 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/31 16:22:48 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing_input_state_machine.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_s(t_fsm *fsm, char c)
{
	if (c == '\'')
		fsm->current_state = idle;
	else if (c == '\0')
		parsing_error(fsm, "'");
	else
		add_to_buf(fsm, c);
}

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_d(t_fsm *fsm, char c)
{
	if (c == '\"')
		fsm->current_state = idle;
	else if (c == '\0')
		parsing_error(fsm, "\"");
	else
		add_to_buf(fsm, c);
}
