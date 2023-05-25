/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:47:47 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/25 11:29:49 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../../includes/parsing_meta.h"
#include "../../includes/parsing_meta_state_machine.h"
#include "../../libft/libft.h"

/* Create a node of chained list (meta) */
t_meta	*create_node(char *buffer)
{
	t_meta	*meta_str;

	meta_str = NULL;
	meta_str = (t_meta *)malloc(sizeof(t_meta));
	if (!meta_str)
		parsing_error(meta_str, 0);
	meta_str->content = ft_strdup(buffer);
	if (!meta_str->content)
		parsing_error(meta_str, 0);
	meta_str->next = NULL;
	return (meta_str);
}

/* Get the last element of a chained list */
t_meta	*lst_last(t_meta *meta_strs)
{
	while (meta_strs != NULL && meta_strs->next != NULL)
		meta_strs = meta_strs->next;
	return (meta_strs);
}
