/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:54:32 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/17 13:54:55 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/state_machine.h"
#include "../../libft/libft.h"

t_sm	create_state_machine(char *input);
void	execute_state_machine(t_sm *sm, t_token **tokens, char c);
void	clear_state_machine(t_sm *sm);
void	clear_parsing_error(t_sm *sm, t_token **tokens);

/* State machine. Will loop on each char to know how to separate each token in 
a lineary way. */
t_token	**state_machine(char *input)
{
	t_token	**tokens;
	t_sm	sm;
	int		i;

	sm = create_state_machine(input);
	init_state_machine(&sm);
	tokens = (t_token **)malloc(sizeof(t_token *));
	if (!tokens)
		return (NULL);
	*tokens = NULL;
	i = 0;
	while (i <= (int)ft_strlen(input))
	{
		execute_state_machine(&sm, tokens, input[i]);
		if ((&sm)->current_state == error)
		{
			clear_parsing_error(&sm, tokens);
			return (NULL);
		}
		i++;
	}
	clear_state_machine(&sm);
	if ((&sm)->current_state == stop)
		return (tokens);
	return (NULL);
}

/* Tells state machine what to do depending on current state. Method flexible,
as it is easy to modify and add conditions based on the state you're in. */
void	execute_state_machine(t_sm *sm, t_token **tokens, char c)
{
	if (sm->current_state == idle)
		state_idle(sm, tokens, c);
	else if (sm->current_state == less_than)
		state_less_than(sm, tokens, c);
	else if (sm->current_state == less_than_d)
		state_less_than_d(sm, tokens, c);
	else if (sm->current_state == greater_than)
		state_greater_than(sm, tokens, c);
	else if (sm->current_state == greater_than_d)
		state_greater_than_d(sm, tokens, c);
	else if (sm->current_state == quote_s)
		state_quote_s(sm, c);
	else if (sm->current_state == quote_d)
		state_quote_d(sm, c);
	else if (sm->current_state == s_pipe)
		state_pipe(sm, tokens, c);
}

t_sm	create_state_machine(char *input)
{
	t_sm	sm;

	sm = (t_sm){0};
	sm.input_size = ft_strlen(input);
	sm.current_state = idle;
	sm.type = command;
	return (sm);
}

void	clear_state_machine(t_sm *sm)
{
	if (sm->buf)
		free(sm->buf);
	sm = (t_sm *){0};
}

void	clear_parsing_error(t_sm *sm, t_token **tokens)
{
	clear_state_machine(sm);
	clear_tokens(tokens);
}
