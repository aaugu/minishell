/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:02:32 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 22:09:39 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_input_state_machine.h"

void	state_spaces(t_fsm *fsm, t_token **tokens, char c)
{
	if (c == '\0')
		parsing_error(fsm, "newline");
	else if (c == ' ')
		return ;
	else if ((c != '\0' || c != ' ') && fsm->type == redir_out_ap)
		fsm->current_state = limiter_no_quotes;
	else
		finish_add_state(fsm, tokens, c, idle);
}
