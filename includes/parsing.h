/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:57:48 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/12 13:34:54 by aaugu            ###   ########.fr       */
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
	minus,
	error,
	stop,
}			t_state;

/* Differents possible types of each token */
typedef enum e_type
{
	cmd,
	option,
	redir_in,
	infile,
	heredoc,
	limiter,
	redir_out,
	redir_out_ap,
	outfile,
	t_pipe,
	undefined,
}			t_type;

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

/* State machine */
typedef struct s_sm
{
	enum e_state	current_state;
	char			*buf;
	int				buf_size;
	int				input_size;
	enum e_type		type;
	int				meta;
}					t_sm;

/* Chained list where each parsed elements and their infos are stored */
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

t_token	**parsing(char *input);
void	init_sm(t_sm *sm, t_token **tokens);
t_token	**state_machine(t_sm *sm, char *input);

/* ------------------------------ PARSING ERROR -----------------------------*/
void	parsing_error(t_sm *sm, t_token **tokens, char *c);

#endif