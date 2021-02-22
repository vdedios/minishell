/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 16:15:45 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_export(t_shell *shell)
{
	int ret;

	ret = 0;
	delete_environment(shell, "_", shell->env);
	ret = ft_export(shell, NULL);
	return (ret);
}

int		exec_env(t_shell *shell)
{
	char	*lower;
	char	*path;
	char	*tmp;

	lower = to_lower(shell->args[0]);
	if (ft_strcmp(lower, "env"))
	{
		path = get_path(shell);
		tmp = ft_strjoin("_=", path);
		free(path);
		ft_export(shell, tmp);
		free(tmp);
		free(lower);
		return (ft_env(shell, shell->env));
	}
	free(lower);
	return (0);
}

char	*get_var_key(char *line, int it)
{
	int		i;
	int		k;
	char	*key;

	i = it;
	k = 0;
	while (i >= 0 && line[i] != '{')
		i--;
	if (!(key = malloc((it - i) * sizeof(char))))
		return (NULL);
	i++;
	while (i < it)
		key[k++] = line[i++];
	key[k] = '\0';
	return (key);
}

short	contain_spaces(char *value)
{
	while (*value)
	{
		if (*value == ' ')
			return (1);
		value++;
	}
	return (0);
}
