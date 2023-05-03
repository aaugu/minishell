/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:59:00 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/01 13:59:00 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************
*							    INCLUDE										  *
******************************************************************************/
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../libft/libft.h"

/******************************************************************************
*								MACROS										  *
******************************************************************************/
typedef unsigned char		t_uint8_t;
typedef t_uint8_t			t_bool;
# define FALSE 0u
# define TRUE  1u

/******************************************************************************
*							 GLOBAL VARIABLE		  						  *
******************************************************************************/

int				g_exit_code;

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

typedef struct s_parsing
{
	int			save;
	int			size;
}				t_parsing;

typedef struct s_data
{
	char        **envp;
	char		*user_input;
	char        **input;
	t_parsing   parsing;
	int         exit_code;
}					t_data;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

/* ------------------------------ TOOLS -------------------------------------*/
//utils.c
void				ft_title(void);
//signal.c
void				ft_ctrlc(int sig);
void                ft_ctrld(t_data *data);

/* ---------------------------- EXECUTION -----------------------------------*/
//exemple1.c

/* ------------------------------ PARSER ------------------------------------*/
//exemple2.c

#endif