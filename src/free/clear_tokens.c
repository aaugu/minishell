/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:42:21 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/20 01:37:43 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "parsing_input.h"

/* Clear token chained list */
void	clear_tokens(t_token **tokens)
{
	t_token	*next;

	while (*tokens != NULL)
	{
		next = (*tokens)->next;
		if ((*tokens)->content)
			free((*tokens)->content);
		free(*tokens);
		*tokens = next;
	}
}
