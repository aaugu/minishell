/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:31:01 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/15 11:09:05 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "../../../includes/parsing_meta_heredoc_state_machine.h"
#include "../../../libft/libft.h"

void	execute_hd_s_machine(t_m_fsm *fsm, t_meta **metas, char c, int last_e);

/* Finite state machine. Will loop on each char to know how to separate and
interpret as meta char each element in a lineary way. */
t_meta	*heredoc_state_machine(char *str, char **env, int env_size, int last_e)
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
		if (fsm.current_state == error)
			break ;
		else
			execute_hd_s_machine(&fsm, &meta_strs, str[i], last_e);
		i++;
	}
	clear_meta_state_machine(&fsm);
	if (fsm.current_state == stop)
		return (meta_strs);
	return (NULL);
}

/* Tells state machine what to do depending on current state. Method flexible,
as it is easy to modify and add conditions based on the state you're in. */
void	execute_hd_s_machine(t_m_fsm *fsm, t_meta **metas, char c, int last_e)
{
	if (fsm->current_state == idle)
		state_idle_meta(fsm, metas, c);
	else if (fsm->current_state == dollar)
		state_dollar(fsm, metas, c, last_e);
	else if (fsm->current_state == chars)
		state_chars_heredoc(fsm, metas, c);
	else if (fsm->current_state == stop)
		return ;
}
