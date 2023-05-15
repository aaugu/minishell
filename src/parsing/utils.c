/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:20:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/15 15:45:35 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"
#include "../../includes/parsing.h"

t_token	*create_node(char *buffer, t_type type, t_sm *sm, t_token **tokens)
{
	t_token	*token;

	token = NULL;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		parsing_error(sm, tokens, 0);
	token->content = ft_strdup(buffer);
	if (!token->content)
		parsing_error(sm, tokens, 0);
	token->type = type;
	token->meta = true;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*lst_last(t_token *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
