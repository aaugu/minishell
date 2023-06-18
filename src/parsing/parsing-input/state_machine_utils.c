/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:22:46 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 22:36:06 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../libft/libft.h"

/* Create base of finite state machine */
void	create_state_machine(t_fsm *fsm, char **env, int env_size, char *input)
{
	fsm->buf = NULL;
	fsm->buf_size = 0;
	fsm->input_size = ft_strlen(input);
	fsm->current_state = idle;
	fsm->type = command;
	fsm->tmp = NULL;
	fsm->env_size = env_size;
	fsm->env = ft_strs_copy((const char **)env, env_size);
	if (!fsm->env)
		parsing_error(fsm, NULL);
}

/* Initialize start values of t_fsm state machine */
void	init_state_machine(t_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	fsm->buf = (char *)ft_calloc(fsm->input_size + 1, sizeof(char));
	if (!fsm->buf)
		parsing_error(fsm, 0);
	fsm->buf_size = 0;
	reset_tmp_buf(fsm);
	fsm->quotes = false;
}

/* Clear allocated memory of finite state machine */
void	clear_state_machine(t_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	if (fsm->tmp)
		free(fsm->tmp);
	if (fsm->env)
	{
		ft_strs_free(fsm->env, fsm->env_size);
		fsm->env = NULL;
	}
	fsm = (t_fsm *){0};
}

void	create_content_empty_token(t_fsm *fsm, t_token **tokens)
{
	if (tokens)
		clear_tokens(tokens);
	*tokens = NULL;
	init_state_machine(fsm);
	finish_buf(fsm, tokens, '\0');
}

void	reset_tmp_buf(t_fsm *fsm)
{
	if (fsm->tmp)
		free(fsm->tmp);
	fsm->tmp = (char *)ft_calloc(fsm->input_size + 1, sizeof(char));
	if (!fsm->tmp)
		parsing_error(fsm, 0);
	fsm->tmp_size = 0;
}
