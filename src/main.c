/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:58:27 by aaugu             #+#    #+#             */
/*   Updated: 2023/06/18 21:06:46 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing_input.h"

static char	**ft_copy_env(char **env)
{
	char	**copy_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	copy_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (copy_env == NULL)
		return (NULL);
	j = 0;
	while (env[j])
	{
		copy_env[j] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1));
		if (copy_env[j] == NULL)
			return (NULL);
		ft_strlcpy(copy_env[j], env[j], ft_strlen(env[j]) + 1);
		j++;
	}
	copy_env[j] = NULL;
	return (copy_env);
}

static void	ft_good_input(t_data *d)
{
	t_token	*t;

	t = NULL;
	if (ft_strlen(d->user_input) > 0)
	{
		add_history(d->user_input);
		t = parsing_input(d->user_input, d->envp, d->env_size, d->exit_code);
		if (!t)
			clear_minishell(d, g_exit_code);
		if (ft_strlen(t->content) != 0)
			ft_executor(t, d);
		else if (ft_strlen(t->content) == 0 && t->next == NULL)
			ft_executor(t, d);
		if (d->user_input)
			free(d->user_input);
		if (t)
			clear_tokens(&t);
	}
}

static char	*find_trash_path(char **envp)
{
	char	*user;
	char	*home;
	char	*trash_path;
	char	*tmp;

	user = ft_getenv(envp, "USER=");
	if (user != NULL)
	{
		tmp = ft_strdup("/Users/");
		trash_path = ft_strjoin(tmp, user);
		free(tmp);
		free(user);
		tmp = ft_strjoin(trash_path, "/.Trash");
		free(trash_path);
		return (tmp);
	}
	else
	{
		free(user);
		home = ft_getenv(envp, "HOME=");
		if (home != NULL)
			return (home);
	}
	free(user);
	return (NULL);
}

static void	ft_readline(char **envp, t_data *data)
{
	data->envp = ft_copy_env(envp);
	data->env_size = ft_strs_len(data->envp);
	data->trash_path = find_trash_path(data->envp);
	data->exit_code = 0;
	while (1)
	{
		set_signals_interactive();
		data->user_input = readline("minishell > ");
		set_signals_noninteractive();
		if (data->user_input)
		{
			if (g_exit_code != 0)
			{
				data->exit_code = g_exit_code;
				g_exit_code = 0;
			}
			ft_good_input(data);
		}
		else
			ft_ctrld(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	data = (t_data){0};
	ft_title();
	ft_readline(envp, &data);
}
