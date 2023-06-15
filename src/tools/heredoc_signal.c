/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:52:29 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/15 15:19:38 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_reset_prompt_hd(int signo)
{
	(void)signo;
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(1);
}

void	set_signals_interactive_hd(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt_hd;
	sigaction(SIGINT, &act, NULL);
}
