/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:57:48 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/05 13:41:38 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/
# include "libft.h"
# include "parsing.h"

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

/* Differents possible states of state machine */
typedef enum e_state
{
	idle,
	less_than,
	less_than_d,
	greater_than,
	greater_than_d,
	backslash,
	quote_s,
	quote_d,
	pipe,
	error,
	stop,
}			t_state;

/* State machine */
typedef struct s_state_machine
{
	char			*buf;
	int				buf_size;
	enum t_state	current_state;
}					t_state_machine;

/* Chained list where each parsed elements are stored */
typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

t_list	*parsing(char *input);
t_token	*state_machine(t_state_machine *sm, char *input);

#endif