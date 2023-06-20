/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:55:39 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/20 13:38:39 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "parsing_input_state_machine.h"
#include "parsing_meta.h"
#include "libft.h"

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_s(t_fsm *fsm, t_token **tokens, char c)
{
	t_token	*new_token;
	t_token	*prev;

	if (c == '\'' && fsm->buf_size == 0)
	{
		new_token = create_node(fsm);
		if (!new_token)
			parsing_error(fsm, 0);
		if (*tokens == NULL)
			*tokens = new_token;
		else
		{
			prev = lst_last(*tokens);
			prev->next = new_token;
			new_token->prev = prev;
		}
		init_state_machine(fsm);
		get_next_type(fsm, c);
	}
	if (c == '\'')
		change_state_quotes(fsm, idle);
	else if (c == '\0')
		parsing_error(fsm, "'");
	else
		add_to_buf(fsm, c);
}

/* Will set current state according to char and decide which action to perform
if needed */
void	state_quote_d(t_fsm *fsm, t_token **tokens, char c)
{
	t_token	*new_token;
	t_token	*prev;

	if (c == '\"' && fsm->buf_size == 0)
	{
		new_token = create_node(fsm);
		if (!new_token)
			parsing_error(fsm, 0);
		if (*tokens == NULL)
			*tokens = new_token;
		else
		{
			prev = lst_last(*tokens);
			prev->next = new_token;
			new_token->prev = prev;
		}
		init_state_machine(fsm);
		get_next_type(fsm, c);
	}
	if (c == '\"')
		change_state_quotes(fsm, idle);
	else if (c == '$')
	{
		add_to_tmp_buf(fsm, c);
		fsm->current_state = dollar_quotes;
	}
	else if (c == '\0')
	{
		parsing_error(fsm, "\"");
	}
	else
		add_to_buf(fsm, c);
}
