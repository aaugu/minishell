/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:39 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 15:45:32 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"
#include "../../includes/parsing.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_s(t_sm *sm, t_token **tokens, char c)
{
	if (c == '\'')
		sm->current_state = idle;
	else if (c == '\0')
		parsing_error(sm, tokens, "'");
	else
		add_to_buf(sm, c);
}

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_d(t_sm *sm, t_token **tokens, char c)
{
	if (c == '\"')
		sm->current_state = idle;
	else if (c == '\0')
		parsing_error(sm, tokens, "\"");
	else
		add_to_buf(sm, c);
}
