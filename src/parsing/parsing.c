/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:18:11 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/05 13:46:29 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

void	init_state_machine(t_state_machine *sm, char *input);

/* Parsing to retrieve each separate elements (tokens) of user input as an 
element of the command and store them in a chained list. */
t_list	*parsing(char *input)
{
	t_state_machine	sm;
	t_token			*tokens;

	init_state_machine(&sm, input);
	tokens = state_machine(&sm, input);
	if (!tokens)
		exit(EXIT_FAILURE);
	return (tokens);
}

/* Initialize start values of state machine */
void	init_state_machine(t_state_machine *sm, char *input)
{
	sm->current_state = idle;
	sm->buf_size = 0;
	sm->buf = (char *)ft_calloc(ft_strlen(input), sizeof(char));
	if (!sm->buf)
		exit(EXIT_FAILURE);
}
