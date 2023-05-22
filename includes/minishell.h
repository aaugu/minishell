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
# include "parsing.h"

/******************************************************************************
*								MACROS										  *
******************************************************************************/

// Standard fd
# define STDIN 0
# define STDOUT 1
# define STDERR 2

/******************************************************************************
*							 GLOBAL VARIABLE		  						  *
******************************************************************************/

int	g_exit_code;

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

typedef struct s_data
{
    char	**envp;
    char	*user_input;
    int		exit_code;
	char	**cmd;
	int		cmd_nbr;
	int		pipe_nbr;
	char	**all_path;
	int		*fd_array;
	t_token	**tokens;
}					t_data;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

/* ------------------------------ TOOLS -------------------------------------*/
//utils.c
void		ft_title(void);
//signal.c
void		ft_ctrlc(int sig);
void		ft_ctrld(t_data *data);

/* ---------------------------- EXECUTION -----------------------------------*/
//exemple1.c

/* ------------------------------ PARSER ------------------------------------*/
//exemple2.c
void		rl_replace_line(const char *, int);
void		rl_clear_history(void);

void		clear_minishell(t_data *data);

#endif