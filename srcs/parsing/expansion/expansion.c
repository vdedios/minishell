/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 09:03:31 by vde-dios          #+#    #+#             */
/*   Updated: 2021/02/18 19:39:35 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*get_env_value(t_shell *shell, char *delimiter, int i)
{
	char	*ret;
	char	*value;

	if (shell->env[i])
		value = ft_strdup(ft_strchr(shell->env[i], '=') + 1);
	else
		value = ft_strdup("");
	escape_char_safe(&value, '\\');
	if (delimiter && *(delimiter - 1) == ' ')
		escape_char_safe(&value, ' ');
	if (delimiter && *delimiter)
	{
		delimiter++;
		ret = ft_strjoin(value, delimiter);
	}
	else
		ret = ft_strdup(value);
	free(value);
	return (ret);
}

char			*expand_var(char *env, t_shell *shell)
{
	int		i;
	int		len;
	char	*delimiter;

	i = 0;
	delimiter = NULL;
	if (*env == '{')
	{
		env++;
		delimiter = ft_strchr(env, '}');
		len = ft_strlen(env) - (delimiter ? ft_strlen(delimiter) : 0);
	}
	else
		len = ft_strlen(env);
	if (delimiter && *(delimiter - 1) == ' ')
		len--;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], env, len)
			&& shell->env[i][len] == '=')
			break ;
		else
			i++;
	}
	return (get_env_value(shell, delimiter, i));
}

static	char	*last_proc_status(t_shell *shell, char *env)
{
	free(env);
	return (ft_itoa(shell->previous_stat));
}

static	char	*parse_expansion(t_shell *shell, char **env_split,
								short first_is_env)
{
	int		len;
	char	*buff;
	char	*tmp;

	len = 0;
	buff = ft_strdup("");
	while (env_split[len])
		len++;
	while (--len >= 0)
	{
		if (env_split[len][1] == '?' && !env_split[len][3])
			env_split[len] = last_proc_status(shell, env_split[len]);
		else if (len || first_is_env)
		{
			tmp = ft_strdup(env_split[len]);
			free(env_split[len]);
			env_split[len] = expand_var(tmp, shell);
			free(tmp);
		}
		tmp = ft_strdup(buff);
		free(buff);
		buff = append_expanded(tmp, env_split[len]);
		free(tmp);
	}
	return (buff);
}

char			*expansion(t_shell *shell, char *str)
{
	char	**env_split;

	str = escape_char(str, '$');
	env_split = ft_split_non_escaped(str, '$');
	if (env_split[0])
	{
		if (env_split[1] || (*env_split[0] != *str))
		{
			free(str);
			str = parse_expansion(shell, env_split, (short)(*str == '$'));
		}
	}
	clean_matrix(env_split);
	free(env_split);
	return (str);
}
