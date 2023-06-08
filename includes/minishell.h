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
# include "parsing_input.h"

/******************************************************************************
*								MACROS										  *
******************************************************************************/

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

int	g_exit_code;

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
	int				env_size;
	char			*user_input;
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

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/
/* ---------------------------- BUILTINS ------------------------------------*/
//builtin.c
int					ft_is_builtins(t_token *token);
void				ft_which_builtins(t_data *data, t_token *token, pid_t *pid);
void				ft_which_builtins_child(t_data *data);

int					ft_cd(t_data *data);
int					ft_pwd(void);
int					ft_export(t_data *data);
void				ft_echo(t_data *data);

//utils.c
void				ft_oldpwd(t_data *data, char *old_cd);
void				ft_change_oldpwd(t_data *data, char *old_cd);
int					len_equal(char *str);
int					ft_only_digit(char *str);
int					ft_other_than_alnum(char *str);
int					ft_digit_equal(char *str);
int					ft_export_nbr(t_data *data);
char				**copy_exist(t_data *data, int line, int nbr, int *i);
char				*ft_dup_export(char **export, t_data *d, int *i, int j);
int					ft_does_it_exist(int i, int j, char **export, t_data *data);
char				**ft_add(int line, int export_nbr, t_data *data);

/* ---------------------------- EXECUTION -----------------------------------*/
//child.c
void				ft_process_child(t_data *d, t_token *tmp, pid_t *p);
void				ft_child_error(t_token *token, t_data *d, int flag);
//count.c
int					ft_mark_count(t_token *token, t_type type);
//cmd.c
void				ft_builtins_or_cmd(t_data *d, t_token *tmp, pid_t *pid);
char				**ft_find_cmd(t_token *token);
char				*ft_getenv(char **envp, char *var);
int					ft_is_cmd(t_token *token);
//count.c
int					ft_pipe_count(t_token *token);
int					ft_cmd_count(t_token *token);
//error.c
void				ft_exit_doc(t_token *token, t_data *data);
void				ft_cmd_error(t_data *data);
void				ft_too_much_pipe(int *fd_array, int pipe_nbr);
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
char				*ft_launcher(t_data *data);

//pipe.c
void				ft_pipe_doc(t_data *data);
int					*ft_set_pipe(t_data *data);
void				ft_pipe_child(t_data *data, t_token *token);
//redir.c
void				ft_redirection(t_token *tmp, t_data *data);

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

void				meta_interpret(t_token *token, char **env, int env_size);
void				clear_minishell(t_data *data);

#endif
