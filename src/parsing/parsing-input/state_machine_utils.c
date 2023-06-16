/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:22:46 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/16 10:19:39 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../libft/libft.h"

/* Initialize start values of t_fsm state machine */
void	init_state_machine(t_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	fsm->buf = (char *)ft_calloc(fsm->input_size + 1, sizeof(char));
	if (!fsm->buf)
		parsing_error(fsm, 0);
	fsm->buf_size = 0;
	fsm->meta = true;
}

void	create_content_empty_token(t_fsm *fsm, t_token **tokens)
{
	if (tokens)
		clear_tokens(tokens);
	*tokens = NULL;
	init_state_machine(fsm);
	finish_buf(fsm, tokens, '\0');
}
