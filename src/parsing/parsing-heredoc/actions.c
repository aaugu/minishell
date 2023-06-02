/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:30:15 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/02 15:47:29 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
// #include "../../../includes/parsing_meta_state_machine.h"
// #include "../../../libft/libft.h"

// t_meta	*create_node_meta(char *buffer, t_m_fsm *fsm);
// t_meta	*lst_last_meta(t_meta *meta_strs);

// /* Add char to current buffer */
// void	add_to_buf_meta(t_m_fsm *fsm, char c)
// {
// 	fsm->buf[fsm->buf_size] = c;
// 	fsm->buf_size++;
// }

// void	finish_buf_meta(t_m_fsm *fsm, t_meta **meta_strs)
// {
// 	t_meta	*new_meta;
// 	t_meta	*last;

// 	if (fsm->buf_size != 0)
// 	{
// 		new_meta = create_node_meta(fsm->buf, fsm);
// 		if (!new_meta)
// 			parsing_error_meta(&(fsm->current_state));
// 		if (*meta_strs == NULL)
// 			*meta_strs = new_meta;
// 		else
// 		{
// 			last = lst_last_meta(*meta_strs);
// 			last->next = new_meta;
// 		}
// 		init_meta_state_machine(fsm);
// 	}
// }

// t_meta	*create_node_meta(char *buffer, t_m_fsm *fsm)
// {
// 	t_meta	*meta;

// 	meta = NULL;
// 	meta = (t_meta *)malloc(sizeof(t_meta));
// 	if (!meta)
// 		parsing_error_meta(&(fsm->current_state));
// 	if (buffer)
// 		meta->content = ft_strdup(buffer);
// 	if (!meta->content)
// 		parsing_error_meta(&(fsm->current_state));
// 	meta->next = NULL;
// 	return (meta);
// }

// /* Get the last element of a chained list */
// t_meta	*lst_last_meta(t_meta *meta_strs)
// {
// 	while (meta_strs->next != NULL)
// 		meta_strs = meta_strs->next;
// 	return (meta_strs);
// }
