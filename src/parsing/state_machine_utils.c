/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:22:46 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/17 15:16:00 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/state_machine.h"
#include "../../includes/minishell.h"

/* Initialize start values of t_sm state machine */
void	init_state_machine(t_sm *sm)
{
	if (sm->buf)
		free(sm->buf);
	sm->buf = (char *)ft_calloc(sm->input_size, sizeof(char));
	if (!sm->buf)
		parsing_error(sm, 0);
	sm->buf_size = 0;
	sm->meta = true;
}
