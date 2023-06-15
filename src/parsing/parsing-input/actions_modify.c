/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_modify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:03:33 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/15 13:30:02 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../includes/parsing_meta_heredoc.h"
#include "../../../libft/libft.h"

/* Add char to current buffer */
void	add_to_buf(t_fsm *fsm, char c)
{
	fsm->buf[fsm->buf_size] = c;
	fsm->buf_size++;
}

/* Change state and add on-going type */
void	change_state_and_type(t_fsm *fsm, t_state state, t_type type)
{
	if (state)
		fsm->current_state = state;
	if (type)
		fsm->type = type;
}

/* Combination of change_state_and_type() and add_to_buf() */
void	state_type_add_buf(t_fsm *fsm, t_state state, t_type type, char c)
{
	add_to_buf(fsm, c);
	change_state_and_type(fsm, state, type);
}

/* Change state and set quotes as true */
void	change_state_quotes_true(t_fsm *fsm, t_state state, int last_exit)
{
	char	*meta_str;

	fsm->current_state = state;
	fsm->quotes = true;
	if (fsm->meta == true && ft_strnstr(fsm->buf, "$", 1))
	{
		meta_str = parsing_meta(fsm->buf, fsm->env, fsm->env_size, last_exit);
		if (!meta_str)
			parsing_error(fsm, NULL);
		free(fsm->buf);
		fsm->buf = NULL;
		fsm->buf = (char *)ft_calloc((ft_strlen(meta_str) + fsm->input_size \
		+ 1), sizeof(char));
		if (!fsm->buf)
			parsing_error(fsm, NULL);
		ft_strlcpy(fsm->buf, meta_str, ft_strlen(meta_str) + 1);
		free(meta_str);
		fsm->buf_size = ft_strlen(fsm->buf);
	}
}
