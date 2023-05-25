/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:38:09 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/25 14:21:21 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../../includes/parsing_meta_state_machine.h"
#include "../../includes/minishell.h"
#include "../../includes/print_error.h"
#include "../../libft/libft.h"

void	remove_dollar(char **buf, int *buf_size);

void	state_dollar(t_m_fsm *fsm, t_meta **meta_strs, char c)
{
	if (c == '?')
	{
		free(fsm->buf);
		fsm->buf = ft_itoa(g_exit_code);
		if (!fsm->buf)
		{
			g_exit_code = print_err("minishell: malloc() failed: %s\n", errno);
			fsm->current_state = error;
			return ;
		}
		finish_buf_meta();
		fsm->current_state = idle;
	}
	else if (c == '\0')
		fsm->current_state = stop;
	else
	{
		remove_dollar(&(fsm->buf), &(fsm->buf_size));
		add_to_buf_meta(fsm, c);
		fsm->current_state = chars;
	}
}

void	remove_dollar(char **buf, int *buf_size)
{
	*buf[*buf_size - 1] = '\0';
	*buf_size--;
}
