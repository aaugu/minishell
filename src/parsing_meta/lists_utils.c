/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:47:47 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/23 15:20:01 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "parsing_meta.h"

/* Create a node of chained list (meta) */
t_meta	*create_node(char *buffer)
{
	t_meta	*meta;

	meta = NULL;
	meta = (t_meta *)malloc(sizeof(t_meta));
	if (!meta)
		parsing_error(meta, 0);
	meta->content = ft_strdup(buffer);
	if (!meta->content)
		parsing_error(meta, 0);
	meta->next = NULL;
	return (meta);
}

/* Get the last element of a chained list */
t_meta	*lst_last(t_meta *meta)
{
	while (meta != NULL && meta->next != NULL)
		meta = meta->next;
	return (meta);
}
