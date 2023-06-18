/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:39 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 16:56:11 by aaugu            ###   ########.fr       */
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
	// if ((c == '?' || c == '\0' || c == '\'' || c == '/' || c == '-'))
	// {
	// 	change_buf_to_var_content(fsm);
	// }
	if (c == '$')
		state_type_add_buf(fsm, dollar_quotes, fsm->type, c);
	else if (c == '\"')
		change_state_quotes(fsm, idle);
	else if (c == '\0')
		parsing_error(fsm, "\"");
	else
		add_to_buf(fsm, c);
}
