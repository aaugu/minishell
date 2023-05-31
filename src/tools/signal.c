/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:41:22 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/26 11:28:08 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_free_double(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
	str = NULL;
	return (NULL);
}

void	ft_ctrlc(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 130;
}

void	ft_ctrld(t_data *data)
{
	printf("exit\n");
	rl_clear_history();
	ft_free_double(data->envp);
	exit(EXIT_SUCCESS);
}

void	ft_quit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(3);
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