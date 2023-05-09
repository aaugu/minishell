/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:57:48 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/09 13:54:42 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/

# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>

/******************************************************************************
*								ENUM									      *
******************************************************************************/

/* Differents possible states of state machine */
typedef enum e_state
{
	idle,
	less_than,
	less_than_d,
	greater_than,
	greater_than_d,
	quote_s,
	quote_d,
	pipes,
	error,
	stop,
}			t_state;

typedef enum e_type
{
	cmd,
	great,
	great_great,
	less,
	less_less,
	t_pipe,
	file,
	undefined,
}			t_type;

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

/* State machine */
typedef struct s_state_machine
{
	enum e_state	current_state;
	char			*buf;
	int				buf_size;
	int				input_size;
	int				quotes_d;
}					t_state_machine;

/* Chained list where each parsed elements are stored */
typedef struct s_token
{
	char			*content;
	enum e_type		type;
	int				meta;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

t_token	*parsing(char *input);
void	init_state_machine(t_state_machine *sm, t_token *tokens);
t_token	*state_machine(t_state_machine *sm, char *input);

/* ------------------------------ PARSING ERROR -----------------------------*/
void	parsing_error(t_state_machine *sm, t_token **tokens, char c);

#endif