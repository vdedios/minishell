/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:45:32 by migferna          #+#    #+#             */
/*   Updated: 2021/02/19 20:16:29 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**process_envs(char **env)
{
	char	**tmp_envp;
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	tmp_envp = ft_strdup_matrix(env);
	while (tmp_envp[i])
	{
		tmp = ft_strjoin("declare -x ", tmp_envp[i]);
		tmp2 = add_quotes_and_backslash(tmp);
		free(tmp_envp[i]);
		free(tmp);
		tmp_envp[i] = tmp2;
		i++;
	}
	return (tmp_envp);
}

size_t	print_sorted_env(t_shell *shell)
{
	char **tmp_envp;
	char **tmp_envp2;

	tmp_envp = sort_alpha(ft_strdup_matrix(shell->env));
	tmp_envp2 = process_envs(tmp_envp);
	ft_env(shell, tmp_envp2);
	clean_matrix(tmp_envp);
	free(tmp_envp);
	clean_matrix(tmp_envp2);
	free(tmp_envp2);
	return (1);
}

void	export_values(t_shell *shell, char *last_arg, int j)
{
	int		i;
	int		key_len;
	char	*value;
	char	*tmp;
	char	**tmp_env;

	i = 0;
	if (last_arg)
		value = ft_strdup(last_arg);
	else
		value = ft_strdup(shell->args[j]);
	tmp = ft_strchr(value, '=');
	key_len = ft_strlen(value) - ft_strlen(tmp);
	while (shell->env[i]
			&& ft_strncmp_equal(shell->env[i], value, key_len))
		i++;
	tmp = ft_strdup(value);
	free(value);
	value = parse_backslash(tmp, 2);
	free(tmp);
	tmp_env = add_env(&value, shell->env, i);
	clean_env(shell);
	free(value);
	shell->env = tmp_env;
}

int		ft_export(t_shell *shell, char *last_arg)
{
	char	*tmp;
	int		j;

	j = 1;
	if (last_arg && has_valid_name(last_arg))
		export_values(shell, last_arg, 0);
	else if (last_arg)
		not_valid_keyname(shell, last_arg, "export");
	else if (!shell->args[j])
		return (print_sorted_env(shell));
	else
	{
		while (shell->args[j])
		{
			if (!has_valid_name(shell->args[j]))
				not_valid_keyname(shell, shell->args[j], "export");
			else if ((tmp = ft_strchr(shell->args[j], '='))
					&& *tmp != *shell->args[j])
				export_values(shell, last_arg, j);
			j++;
		}
	}
	return (1);
}
