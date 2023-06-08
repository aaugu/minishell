/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:31:01 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/05 16:43:23 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "../../../includes/parsing_meta_heredoc_state_machine.h"
#include "../../../libft/libft.h"

void	execute_heredoc_state_machine(t_m_fsm *fsm, t_meta **metas, char c);

/* Finite state machine. Will loop on each char to know how to separate and
interpret as meta char each element in a lineary way. */
t_meta	*heredoc_state_machine(char *str, char **env, int env_size)
{
	t_m_fsm	fsm;
	t_meta	*meta_strs;
	int		i;

	create_meta_fsm(&fsm, env, env_size, str);
	if (!fsm.env)
		return (NULL);
	init_meta_state_machine(&fsm);
	meta_strs = NULL;
	i = 0;
	while (i <= (int)ft_strlen(str))
	{
		execute_heredoc_state_machine(&fsm, &meta_strs, str[i]);
		if (fsm.current_state == error)
			break ;
		i++;
	}
	clear_meta_state_machine(&fsm);
	if (fsm.current_state == stop)
		return (meta_strs);
	return (NULL);
}

/* Tells state machine what to do depending on current state. Method flexible,
as it is easy to modify and add conditions based on the state you're in. */
void	execute_heredoc_state_machine(t_m_fsm *fsm, t_meta **metas, char c)
{
	if (fsm->current_state == idle)
		state_idle_meta(fsm, metas, c);
	else if (fsm->current_state == dollar)
		state_dollar(fsm, metas, c);
	else if (fsm->current_state == chars)
		state_chars_heredoc(fsm, metas, c);
	else if (fsm->current_state == stop)
		return ;
}
