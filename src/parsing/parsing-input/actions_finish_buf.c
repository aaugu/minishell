/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_finish_buf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:59:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/12 15:03:00 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../libft/libft.h"

char	*get_final_buffer(char *buf, int buf_size, t_type type, int meta);
t_token	*create_node(t_fsm *fsm);
t_token	*lst_last(t_token *token);
void	get_next_type(t_fsm *fsm, char c);

/* Finish buffer, create a node of tokens list and set its content. Then reset
state machine. Get type of next node.*/
void	finish_buf(t_fsm *fsm, t_token **tokens, char c)
{
	t_token	*new_token;
	t_token	*prev;

	if (fsm->buf_size != 0 || c == '\0')
	{
		fsm->buf[fsm->buf_size] = '\0';
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
	token->meta = fsm->meta;
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
	if (fsm->type == redir_in || fsm->type == heredoc || fsm->type == redir_out \
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
