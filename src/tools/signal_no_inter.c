/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_no_inter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:50:51 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/16 09:51:05 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_quit_newline(int signal)
{
	(void)signal;
	write(1, "Quit: 3\n", 8);
	rl_on_new_line();
	g_exit_code = 131;
}

void	signal_print_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	g_exit_code = 130;
}

void	set_signals_noninteractive(void)
{
	struct sigaction	act;
	struct sigaction	act_bis;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	act_bis.sa_handler = &signal_quit_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act_bis, NULL);
}
