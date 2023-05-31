/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:33 by lvogt             #+#    #+#             */
/*   Updated: 2023/05/31 10:20:25 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}


int	ft_only_digit(char *str)
{
	int	i;
	int	forbiden;

	i = 0;
	forbiden = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isdigit(str[i]) == 1)
			forbiden++;
		else if (str[i] != '_' && ft_isalpha(str[i]) != 1)
			forbiden++;
		i++;
	}
	if (forbiden == len_equal(str))
		return (1);
	return (0);
}

int	ft_other_than_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
		{
			if (str[i] != '_')
				return (1);
		}
		i++;
	}
	if (str[i] && str[i] == '=')
		return (0);
	return (1);
}

int	ft_digit_equal(char *str)
{
	int	flag;

	flag = 0;
	flag += ft_only_digit(str);
	flag += ft_other_than_alnum(str);
	if (flag > 0)
		return (1);
	return (0);
}

int	ft_export_nbr(t_data *data)
{
	int	i;
	int	export_nbr;

	i = 1;
	export_nbr = 0;
	while (data->cmd[i])
	{
		if (ft_digit_equal(data->cmd[i]) == 0)
			export_nbr++;
		else
		{
			write(2, "minishell: export: ", 19);
			write(2, data->cmd[i], ft_strlen(data->cmd[i]));
			write(2, ": not a valid identifier\n", 25);
		}
		i++;
	}
	return (export_nbr);
}

char	**copy_exist(t_data *data, int line, int export_nbr, int *i)
{
	char	**export;

	export = (char **)ft_calloc((line + export_nbr + 1), sizeof(char *));
	if (!export)
		return (NULL);
	while (*i < line)
	{
		export[*i] = ft_strdup(data->envp[*i]);
		if (!export[*i])
			return (NULL);
		*i += 1;
	}
	return (export);
}

static char	*ft_dup_export(char **export, t_data *d, int *i, int j)
{
	export[*i] = ft_strdup(d->cmd[j]);
	if (!export[*i])
		return (NULL);
	*i += 1;
	return (export[*i]);
}

int	ft_does_it_exist(int i, int j, char **export, t_data *data)
{
	int	n;

	n = 0;
	while (n < i)
	{
		if (ft_strncmp(export[n], data->cmd[j], len_equal(data->cmd[j])) == 0)
			return (n);
		n++;
	}
	return (-1);
}

char	**ft_add(int line, int export_nbr, t_data *data)
{
	char	**export;
	int		exist;
	int		i;
	int		j;

	j = 0;
	i = 0;
	export = copy_exist(data, line, export_nbr, &i);
	while (data->cmd[++j])
	{
		exist = ft_does_it_exist(i, j, export, data);
		if (ft_digit_equal(data->cmd[j]) == 0)
		{
			if (exist >= 0)
			{
				free(export[exist]);
				export[exist] = ft_strdup(data->cmd[j]);
			}
			else
				export[i] = ft_dup_export(export, data, &i, j);
		}
	}
	export[i] = NULL;
	return (export);
}

void	sort_env_alph(char **env_copy, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strncmp(env_copy[i], env_copy[j], 255) > 0)
			{
				temp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = temp;
			}
			j++;
		}
	}
}

void	ft_env_alph_order(char **env)
{
	int		i;
	int		count;
	char	**copy;

	count = 0;
	i = -1;
	while (env[count])
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	while (++i < count)
		copy[i] = env[i];
	copy[count] = NULL;
	sort_env_alph(copy, count);
	i = -1;
	while (++i < count)
		printf("declare -x %s\n", copy[i]);
	free(copy);
}

int	ft_export(t_data *data)
{
	int		export_nbr;
	int		line;
	char	**export;

	line = 0;
	if (!data->cmd[1])
		ft_env_alph_order(data->envp);
	else if (data->cmd[1])
	{
		export_nbr = ft_export_nbr(data);
		if (data->cmd_nbr == 1)
		{
			while (data->envp[line])
				line++;
			export = ft_add(line, export_nbr, data);
			ft_free_double(data->envp);
			data->envp = export;
		}
	}
	return (0);
}
