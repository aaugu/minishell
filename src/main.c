/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:58:27 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/16 13:01:35 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"

char	**ft_copy_env(char **env)
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

static void	ft_good_input(t_data *data)
{
	if (ft_strlen(data->user_input) > 0)
	{
		add_history(data->user_input);
		parsing(data->user_input);
		if (data->user_input)
			free(data->user_input);
	}
}

static void	ft_readline(char **envp, t_data *data)
{
	data->envp = ft_copy_env(envp);
	data->exit_code = 0;
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_exit_code = 0;
		data->user_input = readline("minishell > ");
		if (data->user_input)
		{
			if (g_exit_code != 0)
				data->exit_code = g_exit_code;
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
