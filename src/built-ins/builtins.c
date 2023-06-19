/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:01:39 by lvogt             #+#    #+#             */
/*   Updated: 2023/06/19 12:47:40 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/built_ins.h"

/* ft_which_builtins_child:
 *	Gère export sans option, pwd, env et echo.
 */
void	ft_which_builtins_child(t_data *data)
{
	int		error;

	error = 0;
	if (data->is_builtin == 4 && !data->cmd[1])
		ft_export(data);
	else if (data->is_builtin == 5)
		ft_pwd();
	else if (data->is_builtin == 6)
		cmd_env(data->envp, data->env_size, data->cmd);
	else if (data->is_builtin == 7)
		error = ft_echo(data);
	g_exit_code = error;
}

/* ft_which_builtins:
 *	Lance le bultin unset, cd, exit ou export avec/sans option.
 */
void	ft_which_builtins(t_data *data)
{
	int		error;

	error = 0;
	if (data->is_builtin == 1)
		error = cmd_unset(data);
	else if (data->is_builtin == 2)
		error = ft_cd(data);
	else if (data->is_builtin == 3)
		error = cmd_exit(data);
	else if (data->is_builtin == 4 && data->cmd[1])
		error = ft_export(data);
	g_exit_code = error;
}

/* ft_len:
 *	Mesure la longeur du content de la struc token jusqu'à un potentiel ' '.
 */
int	ft_len(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp->content[i])
		i++;
	return (i);
}

/* ft_is_builtins:
 *	Donne une valeur à data->is_builtin en fonction
 *	de quel builtin est appelé par la commande
 *	unset = 1 ; cd = 2 ; exit = 3 ; export = 4
 *	pwd = 5 ; env = 6 ; echo = 7 ; -1 si pas un builtin
 */
int	ft_is_builtins(t_token *token)
{
	t_token	*t;

	t = token;
	if (t && t->type == t_pipe)
		t = t->next;
	while ((t && t->type != command) && (t && t->type != t_pipe))
		t = t->next;
	if (t && t->content && t->type == command)
	{
		if (ft_cmp_caps((t->content), "unset", 5) == 0 && ft_len(t) == 5)
			return (1);
		else if (ft_cmp_caps((t->content), "cd", 2) == 0 && ft_len(t) == 2)
			return (2);
		else if (ft_cmp_caps((t->content), "exit", 4) == 0 && ft_len(t) == 4)
			return (3);
		else if (ft_cmp_caps((t->content), "export", 6) == 0 && ft_len(t) == 6)
			return (4);
		else if (ft_cmp_caps((t->content), "pwd", 3) == 0 && ft_len(t) == 3)
			return (5);
		else if (ft_cmp_caps((t->content), "env", 3) == 0 && ft_len(t) == 3)
			return (6);
		else if (ft_cmp_caps((t->content), "echo", 4) == 0 && ft_len(t) == 4)
			return (7);
	}
	return (-1);
}
