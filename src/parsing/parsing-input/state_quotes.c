/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:39 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 20:56:25 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../includes/parsing_meta.h"
#include "../../../libft/libft.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_s(t_fsm *fsm, char c)
{
	if (c == '\'')
		change_state_quotes(fsm, idle);
	else if (c == '\0')
		parsing_error(fsm, "'");
	else
		add_to_buf(fsm, c);
}

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_d(t_fsm *fsm, char c)
{
	if (c == '$')
	{
		add_to_tmp_buf(fsm, c);
		fsm->current_state = dollar_quotes;
	}
	else if (c == '\"')
		change_state_quotes(fsm, idle);
	else if (c == '\0')
		parsing_error(fsm, "\"");
	else
		add_to_buf(fsm, c);
}
