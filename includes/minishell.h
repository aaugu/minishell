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

// Error code.
# define ERR_EXECVE 1
# define ERR_OPEN_LESS 2
# define ERR_OPEN_GREAT 3
# define ERR_DUP2 4
# define ERR_PID 5

/******************************************************************************
*							 GLOBAL VARIABLE		  						  *
******************************************************************************/

int					g_exit_code;

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

typedef struct s_heredoc
{
	int				here_docfd[2];
	int				here_doc_nbr;
	bool			flag_doc;
	char			*str;
}					t_heredoc;

typedef struct s_data
{
	char			**envp;
	char			*input;
	int				exit_code;
	char			**cmd;
	int				cmd_nbr;
	int				pipe_nbr;
	int				great_mark;
	int				less_mark;
	char			**all_path;
	char			*cmd_path;
	int				*fd_array;
	int				is_builtin;
	int				child;
	char			*trash_path;
	int				is_exit_last_cmd;
	t_heredoc		heredoc;

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
/* ---------------------------- BUILTINS ------------------------------------*/
//builtin.c
int					ft_is_builtins(t_token *token);
void				ft_which_builtins(t_data *data, t_token *token, pid_t *pid);

/* ---------------------------- EXECUTION -----------------------------------*/
//child.c
void				ft_process_child(t_data *d, t_token *tmp, pid_t *p);
//cmd.c
void				ft_builtins_or_cmd(t_data *d, t_token *tmp, pid_t *pid);
char				**ft_find_cmd(t_token *token);
char				*ft_getenv(char **envp, char *var);
//count.c
int					ft_pipe_count(t_token *token);
int					ft_cmd_count(t_token *token);
//error.c
void				ft_exit_doc(t_token *token, t_data *data);
//exec.c
void				ft_executor(t_token *token, t_data *data);
//file.c
void				ft_close_fd(int *fd_array, int pipe_nbr);
//heredoc.c
void				ft_heredoc(t_token *token, t_data *data, pid_t *pid2);
int					ft_heredoc_nbr(t_token *t);
int					ft_is_doc_last(t_token *token);
//path.c
char				**ft_find_path(t_data *data);
//pipe.c
void				ft_pipe_doc(t_data *data);
int					*ft_set_pipe(t_data *data);

/* ------------------------------ TOOLS -------------------------------------*/
//utils.c
void				ft_title(void);
//signal.c
void				*ft_free_double(char **str);
void				ft_ctrlc(int sig);
void				ft_ctrld(t_data *data);
void				ft_quit(int sig);
void				ft_sig_n_input(t_data *data);
void				ft_free_child(t_token *token, t_data *d);

/* ------------------------------ PARSER ------------------------------------*/
//exemple2.c

#endif