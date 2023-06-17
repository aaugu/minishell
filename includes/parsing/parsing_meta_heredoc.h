/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_meta_heredoc.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 22:52:18 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/17 22:53:24 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_META_HEREDOC_H
# define PARSING_META_HEREDOC_H

# include "parsing_states.h"

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

typedef struct s_meta
{
	char			*content;
	struct s_meta	*next;
}					t_meta;

typedef struct s_m_fsm
{
	enum e_state	current_state;
	char			*buf;
	char			**env;
	int				buf_size;
	int				env_size;
	int				len;
}					t_m_fsm;

#endif
