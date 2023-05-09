/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:20:19 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/09 11:52:15 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/state_machine.h"

t_token	*create_node(char *buffer, t_token *prev)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(buffer);
	if (!token->content)
		exit(EXIT_FAILURE);
	token->next = NULL;
	token->prev = prev;
	token->type = undefined;
	return (token);
}

t_token	*lst_last(t_token *lst)
{
	while (lst != NULL && lst->next != NULL)
		lst = lst->next;
	return (lst);
}
