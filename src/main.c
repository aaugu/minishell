/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:58:27 by aaugu             #+#    #+#             */
/*   Updated: 2023/05/02 15:49:57 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (ft_strlen(data->input) > 0)
	{
		add_history(data->input);
		//ft_parser(data);
		if (data->input)
			free(data->input);
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
		data->input = readline("minishell > ");
		if (data->input)
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
	(void)ac;
	(void)av;
	t_data	data;
	data = (t_data){0};
    ft_title();
	ft_readline(envp, &data);
}
