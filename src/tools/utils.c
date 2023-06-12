/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:15:38 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/09 13:12:47 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ft_title:
 *	print Minishell en ascii au lancement du programme.
 */
void	ft_title(void)
{
	printf("\033[0;31m\n");
	printf("<-. (`-')    _      <-. (`-')_   _       (`-').->  (`-').->");
	printf("  (`-')  _                     \n");
	printf("   \\(OO )_  (_)        \\( OO) ) (_)      ( OO)_");
	printf("    (OO )__   ( OO).-/    <-.       <-.    \n");
	printf(",--./  ,-.) ,-(`-') ,--./ ,--/  ,-(`-') (_)--\\_)");
	printf("  ,--. ,'-' (,------.  ,--. )    ,--. )   \n");
	printf("|   `.'   | | ( OO) |   \\ |  |  | ( OO) /    _ /");
	printf("  |  | |  |  |  .---'  |  (`-')  |  (`-') \n");
	printf("|  |'.'|  | |  |  ) |  . '|  |) |  |  ) \\_..`--.");
	printf("  |  `-'  | (|  '--.   |  |OO )  |  |OO ) \n");
	printf("|  |   |  |(|  |_/  |  |\\    | (|  |_/  .-._)");
	printf("   \\ |  .-.  |  |  .--'  (|  '__ | (|  '__ | \n");
	printf("|  |   |  | |  |'-> |  | \\   |  |  |'-> \\");
	printf("       / |  | |  |  |  `---.  |     |'  |     |' \n");
	printf("`--'   `--' `--'    `--'  `--'  `--'     `-----'");
	printf("  `--' `--'  `------'  `-----'   `-----'  \n");
	printf("------------------------------------- \033[0;34m");
	printf("aaugu & lvogt \033");
	printf("[0;31m-------------------------------------\n\n\033[0m");
}

/* ft_is_doc_last:
 *	Cherche si la dernière redirection est un heredoc.
 */
int	ft_is_doc_last(t_token *token)
{
	t_token	*tmp;
	int		type;

	tmp = token;
	if (tmp->type == t_pipe)
		tmp = tmp->next;
	type = -1;
	while (tmp && tmp->type != t_pipe)
	{
		if (tmp->type == redir_in || tmp->type == heredoc)
			type = tmp->type;
		tmp = tmp->next;
	}
	if (type == heredoc)
		return (1);
	return (0);
}

/* ft_getenv:
 *	Récupère la ligne ciblé par var dans l'environement.
 */
char	*ft_getenv(char **envp, char *var)
{
	char	*find;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			find = ft_strtrim(envp[i], var);
			return (find);
		}
		i++;
	}
	return (NULL);
}

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
