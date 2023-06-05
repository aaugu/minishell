/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:54:32 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/05 16:39:17 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../includes/parsing_input.h"
#include "../../../libft/libft.h"

void	create_state_machine(t_fsm *fsm, char *input);
void	execute_state_machine(t_fsm *fsm, t_token **tokens, char c);
void	clear_state_machine(t_fsm *fsm);
void	clear_parsing_error(t_fsm *fsm, t_token **tokens);

/* Finite state machine. Will loop on each char to know how to separate each
token in a lineary way. */
t_token	*state_machine(char *input)
{
	t_token	*tokens;
	t_fsm	fsm;
	int		i;

	create_state_machine(&fsm, input);
	init_state_machine(&fsm);
	tokens = NULL;
	i = 0;
	while (i <= (int)ft_strlen(input))
	{
		execute_state_machine(&fsm, &tokens, input[i]);
		if (fsm.current_state == error)
		{
			clear_parsing_error(&fsm, &tokens);
			return (NULL);
		}
		i++;
	}
	clear_state_machine(&fsm);
	if (fsm.current_state == stop)
		return (tokens);
	return (NULL);
}

/* Tells state machine what to do depending on current state. Method flexible,
as it is easy to modify and add conditions based on the state you're in. */
void	execute_state_machine(t_fsm *fsm, t_token **tokens, char c)
{
	if (fsm->current_state == idle)
		state_idle(fsm, tokens, c);
	else if (fsm->current_state == less_than)
		state_less_than(fsm, tokens, c);
	else if (fsm->current_state == less_than_d)
		state_less_than_d(fsm, tokens, c);
	else if (fsm->current_state == greater_than)
		state_greater_than(fsm, tokens, c);
	else if (fsm->current_state == greater_than_d)
		state_greater_than_d(fsm, tokens, c);
	else if (fsm->current_state == quote_s)
		state_quote_s(fsm, c);
	else if (fsm->current_state == quote_d)
		state_quote_d(fsm, c);
	else if (fsm->current_state == s_pipe)
		state_pipe(fsm, tokens, c);
}

/* Create base of finite state machine */
void	create_state_machine(t_fsm *fsm, char *input)
{
	fsm->buf = NULL;
	fsm->buf_size = 0;
	fsm->input_size = ft_strlen(input);
	fsm->current_state = idle;
	fsm->type = command;
	fsm->quotes = false;
}

/* Clear allocated memory of finite state machine */
void	clear_state_machine(t_fsm *fsm)
{
	if (fsm->buf)
		free(fsm->buf);
	fsm = (t_fsm *){0};
}

/* If an error is encountered, clear allocated memory of finite state machine
and tokens */
void	clear_parsing_error(t_fsm *fsm, t_token **tokens)
{
	clear_state_machine(fsm);
	clear_tokens(tokens);
}
