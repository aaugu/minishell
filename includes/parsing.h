/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:57:48 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/08 15:20:53 by aaugu            ###   ########.fr       */
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

// Define pour les type d'élement dans l'input pour t_token
# define CMD 1
# define GREAT 2
# define GREAT_GREAT 3
# define LESS 4
# define LESS_LESS 5
# define PIPE 6
# define FILE 7

typedef enum e_type
{
	cmd,
	great,
	great_great,
	less,
	less_less,
	pipe,
	file,
	undefined,
}			t_type;

typedef enum e_boolean
{
	false,
	true,
}			t_boolean;

/* State machine */
typedef struct s_state_machine
{
	char			*buf;
	int				buf_size;
	enum e_state	current_state;
	enum e_boolean	quotes_d;
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