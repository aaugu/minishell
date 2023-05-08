/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_state_machine.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:54:32 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/08 15:25:26 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/state_machine.h"

void	execute_state_machine(char c, t_state_machine *sm, t_token *tokens);

/* State machine to know how to separate each token in a lineary way. Method 
flexible, as it is easy to modify and add conditions based on the state you're
in. */
t_token	*state_machine(t_state_machine *sm, char *input)
{
	t_token	*tokens;
	int		i;

	tokens = create_first_node(sm);
	if (!tokens)
		return (NULL);
	i = 0;
	while (input[i])
	{
		execute_state_machine(input[i], &sm, tokens);
		if (sm->current_state == error)
		{
			clear_state_machine(sm);
			free_tokens(tokens);
			break ;
		}
		i++;
	}
	clear_state_machine(sm);
	if (sm->current_state == stop)
		return (tokens);
	return (NULL);
}

/* Tells what to do depending on current state */
void	execute_state_machine(char c, t_state_machine *sm, t_token *tokens)
{
	if (sm->current_state == idle)
		state_idle(c, sm, tokens);
	if (sm->current_state == less_than)
		state_less_than(c, sm, tokens);
	if (sm->current_state == less_than_d)
		state_less_than_d(c, sm, tokens);
	if (sm->current_state == greater_than)
		state_greater_than(c, sm, tokens);
	if (sm->current_state == greater_than_d)
		state_greater_than_d(c, sm, tokens);
	if (sm->current_state == quote_s)
		state_quote_s(c, sm, tokens);
	if (sm->current_state == quote_d)
		state_quote_d(c, sm, tokens);
	if (sm->current_state == pipe)
		state_pipe(c, sm, tokens);
}

t_token	*create_first_node(t_state_machine *sm)
{
	t_token	*tokens;

	tokens = (t_token *)malloc(sizeof(t_token));
	if (!tokens)
	{
		free_state_machine(sm);
		printf("minishell: malloc: malloc failed");
		return (NULL);
	}
	return (tokens);
}
