/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:39 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/05 15:57:08 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_s(char c, t_state_machine *sm, t_token *tokens)
{
	if (c == '\'')
		sm->current_state = idle;
	else if (c == '\0')
		sm->current_state = error;
	else
		add_buf(c, sm, tokens);
}

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_d(char c, t_state_machine *sm, t_token *tokens)
{
	if (c == '\"')
		sm->current_state = idle;
	else if (c == '\0')
		sm->current_state = error;
	else
		add_buf(c, sm, tokens);
}
