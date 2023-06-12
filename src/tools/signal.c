/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:41:22 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/12 15:23:27 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /* ft_ctrlc:
//  *	si un ctrl-c est utilisé, print un \n et redisplay le prompt
//  */
// void	ft_ctrlc(int sig)
// {
// 	(void)sig;
// 	printf("\ntest1\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	g_exit_code = 1;
// }

/* ft_ctrld:
 *	Dans le cas ou l'input_user est stopé par un ctrl-d ferme minishell.
 */
void	ft_ctrld(t_data *data)
{
	printf("exit\n");
	g_exit_code = 0;
	clear_minishell(data, EXIT_SUCCESS);
}

/* ft_quit:
 *	gère le signal d'interruption durant l'écriture du heredoc
 */
void	ft_quit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(EXIT_FAILURE);
}

/* ft_sig_n_input:
 *	Écoute la présence d'un signal d'interruption
 *	Save l'input dans data->heredoc.str.
 */
void	ft_sig_n_input(t_data *data)
{
	signal(SIGINT, ft_quit);
	data->heredoc.str = readline(">");
}

void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

void	signal_print_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}

void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
