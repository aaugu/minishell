/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:20:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 10:37:39 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../../includes/state_machine.h"
#include "../../includes/parsing.h"
#include "../../libft/libft.h"

/* Create a node of chained list (token) */
t_token	*create_node(char *buffer, t_type type, t_fsm *fsm)
{
	t_token	*token;

	token = NULL;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		parsing_error(fsm, 0);
	token->content = ft_strdup(buffer);
	if (!token->content)
		parsing_error(fsm, 0);
	token->type = type;
	token->meta = true;
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
