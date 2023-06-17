/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:39 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/17 22:10:39 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../includes/parsing_meta.h"
#include "../../../libft/libft.h"

void	change_buf_to_var_content(t_fsm *fsm, int last_exit);

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
void	state_quote_d(t_fsm *fsm, char c, int last_exit)
{
	if ((c == '?' || c == '\0' || c == '\'' || c == '\"' || c == '/' ||
		c == '-') && fsm->meta == true)
		change_buf_to_var_content(fsm, last_exit);
	if (c == '\"')
		change_state_quotes(fsm, idle);
	else if (c == '\0')
		parsing_error(fsm, "\"");
	else
		add_to_buf(fsm, c);
}
