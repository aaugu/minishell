/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:41:22 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/08 14:48:49 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_free_double:
 * fontion qui free un char **
 */
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

/* ft_ctrlc:
 *	si un ctrl-c est utilisé, print un \n et redisplay le prompt
 */
void	ft_ctrlc(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 1;
}

/* ft_ctrld:
 *	Dans le cas ou l'input_user est stopé par un ctrl-d ferme minishell.
 */
void	ft_ctrld(t_data *data)
{
	printf("exit\n");
	g_exit_code = 0;
	clear_minishell(data);
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
