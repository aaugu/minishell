/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_finish_buf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:59:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/19 21:48:54 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "parsing_input_state_machine.h"
#include "parsing_meta.h"
#include "libft.h"
#include "minishell.h"

/* Finish buffer, create a node of tokens list and set its content. Then reset
state machine. Get type of next node.*/
void	finish_buf(t_fsm *fsm, t_token **tokens, char c)
{
	t_token	*new_token;
	t_token	*prev;

	if ((c == '\0' && *tokens == NULL) || fsm->buf_size)
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
}

/* Create a node of chained list (token) */
t_token	*create_node(t_fsm *fsm)
{
	t_token	*token;

	token = NULL;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		parsing_error(fsm, 0);
	if (fsm->buf)
		token->content = ft_strdup(fsm->buf);
	if (!token->content)
		parsing_error(fsm, 0);
	token->type = fsm->type;
	token->quotes = fsm->quotes;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

/* Get the last element of a chained list */
t_token	*lst_last(t_token *token)
{
	while (token != NULL && token->next != NULL)
		token = token->next;
	return (token);
}

/* Define type of next element depending on previous type saved */
void	get_next_type(t_fsm *fsm, char c)
{
	if (fsm->type == redir_in || fsm->type == heredoc || fsm->type == redir_out
		|| fsm->type == redir_out_ap)
	{
		if (fsm->type == redir_in && c == '>')
			fsm->type = redir_out;
		else if (fsm->type == redir_in)
			fsm->type = infile;
		else if (fsm->type == heredoc)
			fsm->type = limiter;
		else if (fsm->type == redir_out)
			fsm->type = outfile;
		else if (fsm->type == redir_out_ap)
			fsm->type = outfile;
	}
	else if (fsm->type == command || fsm->type == option)
		fsm->type = option;
	else
		fsm->type = command;
}
