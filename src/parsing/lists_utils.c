/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:20:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/17 15:14:14 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/minishell.h"
#include "../../includes/state_machine.h"
#include "../../includes/parsing.h"

/* Create a node of chained list (token) */
t_token	*create_node(char *buffer, t_type type, t_sm *sm)
{
	t_token	*token;

	token = NULL;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		parsing_error(sm, 0);
	token->content = ft_strdup(buffer);
	if (!token->content)
		parsing_error(sm, 0);
	token->type = type;
	token->meta = true;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

/* Get the last element of a chained list */
t_token	*lst_last(t_token *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
