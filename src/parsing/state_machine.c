/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:54:32 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/11 14:24:19 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

void	execute_state_machine(char c, t_state_machine *sm, t_token **tokens);

/* State machine to know how to separate each token in a lineary way. Method 
flexible, as it is easy to modify and add conditions based on the state you're
in. */
t_token	**state_machine(t_state_machine *sm, char *input)
{
	t_token	**tokens;
	int		i;

	tokens = (t_token **)malloc(sizeof(t_token *));
	if (!tokens)
		return (NULL);
	*tokens = NULL;
	i = 0;
	while (i <= (int)ft_strlen(input))
	{
		execute_state_machine(input[i], sm, tokens);
		if (sm->current_state == error)
		{
			clear_parsing(sm, tokens);
			return (NULL);
		}
		// printf("char : %c / current state : %d / buffer : %s\n", input[i], sm->current_state, sm->buf);
		i++;
	}
	clear_state_machine(sm);
	if (sm->current_state == stop)
		return (tokens);
	return (NULL);
}

/* Tells what to do depending on current state */
void	execute_state_machine(char c, t_state_machine *sm, t_token **tokens)
{
	if (sm->current_state == idle)
		state_idle(c, sm, tokens);
	else if (sm->current_state == less_than)
		state_less_than(c, sm, tokens);
	else if (sm->current_state == less_than_d)
		state_less_than_d(c, sm, tokens);
	else if (sm->current_state == greater_than)
		state_greater_than(c, sm, tokens);
	else if (sm->current_state == greater_than_d)
		state_greater_than_d(c, sm, tokens);
	else if (sm->current_state == quote_s)
		state_quote_s(c, sm, tokens);
	else if (sm->current_state == quote_d)
		state_quote_d(c, sm, tokens);
	else if (sm->current_state == pipes)
		state_pipe(c, sm, tokens);
}
