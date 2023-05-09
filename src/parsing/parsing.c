/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:18:11 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/09 11:02:37 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

/* Parsing to retrieve each separate elements (tokens) of user input as an 
element of the command and store them in a chained list. */
t_token	*parsing(char *input)
{
	t_state_machine	sm;
	t_token			*tokens;

	sm = (t_state_machine){0};
	sm.input_size = ft_strlen(input);
	init_state_machine(&sm);
	sm.current_state = idle;
	tokens = state_machine(&sm, input);
	if (!tokens)
		exit(EXIT_FAILURE);
	return (tokens);
}

/* Initialize start values of state machine */
void	init_state_machine(t_state_machine *sm)
{
	if (sm->buf)
		free(sm->buf);
	sm->quotes_d = false;
	sm->buf_size = 0;
	sm->buf = (char *)ft_calloc(sm->input_size, sizeof(char));
	if (!sm->buf)
		exit(EXIT_FAILURE);
}
