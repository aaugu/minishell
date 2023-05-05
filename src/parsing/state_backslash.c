/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:08:01 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/05 15:57:01 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_backslash(char c, t_state_machine *sm, t_token *tokens)
{
	if (c == '\0')
		sm->current_state = error;
	else
	{
		add_to_buf(c, sm, tokens);
		sm->current_state = idle;
	}
}
