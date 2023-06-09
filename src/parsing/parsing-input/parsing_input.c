/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:18:11 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/08 13:03:19 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../includes/parsing_input.h"
#include "../../../includes/parsing_input_state_machine.h"
#include "../../../libft/libft.h"

/* Parsing to retrieve each separate elements (tokens) of user input as an 
element of the command and store them in a chained list. */
t_token	*parsing_input(char *input, char **env, int env_size)
{
	t_token	*tokens;

	tokens = state_machine(input, env, env_size);
	if (!tokens)
		return (NULL);
	return (tokens);
}

/* Pour afficher chaque élément séparé avec son type
	printf("0-command\n1-option\n2-redir_in\n3-infile\n4-heredoc\n5-limiter\n\
	6-redir_out\n7-redir_out_ap\n8-outfile\n9-t_pipe\n\n");
	if (tokens)
	{
		while ((*tokens))
		{
			printf("%d : %s\n", (*tokens)->type, (*tokens)->content);
			(*tokens) = (*tokens)->next;
		}
	}
*/