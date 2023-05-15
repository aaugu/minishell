/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:18:11 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 15:46:51 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parsing.h"

/* Parsing to retrieve each separate elements (tokens) of user input as an 
element of the command and store them in a chained list. */
t_token	**parsing(char *input)
{
	t_sm	sm;
	t_token	**tokens;

	tokens = NULL;
	sm = (t_sm){0};
	sm.input_size = ft_strlen(input);
	init_state_machine(&sm, tokens);
	sm.current_state = idle;
	sm.type = cmd;
	tokens = state_machine(&sm, input);
	/*
	printf("0-cmd\n1-option\n2-redir_in\n3-infile\n4-heredoc\n5-limiter\n6-redir_out\n7-redir_out_ap\n8-outfile\n9-t_pipe\n\n");
	printf("Input : \"%s\"\n", input);
	if (tokens)
	{
		while ((*tokens))
		{
			printf("%d : \"%s\"\n", (*tokens)->type, (*tokens)->content);
			(*tokens) = (*tokens)->next;
		}
	}
	return (0);
	*/
	if (!tokens)
		return (NULL);
	return (tokens);
}

/* Initialize start values of state machine */
void	init_state_machine(t_sm *sm, t_token **tokens)
{
	if (sm->buf)
		free(sm->buf);
	sm->meta = true;
	sm->buf_size = 0;
	sm->buf = (char *)ft_calloc(sm->input_size, sizeof(char));
	if (!sm->buf)
		parsing_error(sm, tokens, 0);
}
