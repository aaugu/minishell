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
# include <stdbool.h>
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

// Define pour les type d'élement dans l'input pour t_token
# define CMD 1
# define GREAT 2
# define GREAT_GREAT 3
# define LESS 4
# define LESS_LESS 5
# define PIPE 6
# define FILE 7

// Standard fd
# define STDIN 0
# define STDOUT 1
# define STDERR 2

/******************************************************************************
*							 GLOBAL VARIABLE		  						  *
******************************************************************************/

<<<<<<< HEAD
int				g_exit_code;
=======
int					g_exit_code;
>>>>>>> bed03e4cafa7935a92b68363c41600bae697214a

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
<<<<<<< HEAD
	char        **envp;
	char		*user_input;
	char        **input;
	t_parsing   parsing;
	int         exit_code;
=======
    char			**envp;
    char			*input;
    int				exit_code;
	char			**cmd;
	int				cmd_nbr;
	int				pipe_nbr;
	char			**all_path;
	int				*fd_array;
>>>>>>> bed03e4cafa7935a92b68363c41600bae697214a
}					t_data;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

/* ------------------------------ TOOLS -------------------------------------*/
//utils.c
void				ft_title(void);
//signal.c
void				ft_ctrlc(int sig);
<<<<<<< HEAD
void                ft_ctrld(t_data *data);
=======
void				ft_ctrld(t_data *data);
>>>>>>> bed03e4cafa7935a92b68363c41600bae697214a

/* ---------------------------- EXECUTION -----------------------------------*/
//exemple1.c

/* ------------------------------ PARSER ------------------------------------*/
//exemple2.c

#endif