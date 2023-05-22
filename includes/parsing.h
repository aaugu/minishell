/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:57:48 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/17 15:13:54 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/******************************************************************************
*								ENUM									      *
******************************************************************************/

/* Differents possible types of each token */
typedef enum e_type
{
	command,
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

/* ------------------------------ PARSING ERROR -----------------------------*/
void	clear_tokens(t_token **tokens);

#endif