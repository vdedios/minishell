/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 09:03:31 by vde-dios          #+#    #+#             */
/*   Updated: 2020/12/06 16:07:48 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*append_expanded(char *buff, char *env)
{
	char	*tmp;

	if (*env == '\\' && !(*(env + 1)))
		return (buff);
	tmp = ft_strjoin(env, buff);
	free(env);
	free(buff);
	return (tmp);
}

static	char	*search_delimiters(char	*env)
{
	while (*env)
	{
		if (*env == '\\' || *env == ',')
			return (env);
		env++;
	}
	return (NULL);
}

static	char	*get_env_value(t_shell *shell, char *env, char *delimiters, int i)
{
	char	*ret;
	char	*value;

	if (shell->env[i])
		value = ft_strdup(ft_strchr(shell->env[i], '=') + 1);
	else
		value = ft_strdup("");
	if (delimiters)
	{
		ret = ft_strjoin(value, delimiters);
		free(value);
	}
	else
		ret = value;
	free(env);
	return (ret);
}
static	char	*expand_var(char *env, t_shell *shell)
{
	int		i;
	int		len;
	char	*delimiters;

	i = 0;
	delimiters = search_delimiters(env);
	len = ft_strlen(env) - (delimiters ? ft_strlen(delimiters) : 0);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], env, len)
			&& shell->env[i][len] == '=')
			break;
		else
			i++;
	}
	return (get_env_value(shell, env, delimiters, i));
}

static	char	*last_proc_status(t_shell *shell, char *env)
{
	free(env);
	return (ft_itoa(shell->stat_loc));
}

static	char	*parse_expansion(t_shell *shell, char **env_split, short first_is_env)
{
	int		len;
	char	*buff;

	len = 0;
	buff = ft_strdup("");
	while (env_split[len])
		len++;
	len--;
	while (len >= 0)
	{
		if (env_split[len][0] == '?' && !env_split[len][1])
			env_split[len] = last_proc_status(shell, env_split[len]);
		else if (len || first_is_env)
			env_split[len] = expand_var(env_split[len], shell);
		buff = append_expanded(buff, env_split[len]);
		len--;
	}
	return (buff);
}

static	int		count_single_dollars(char *str)
{
	int		backslashes;
	int		i;

	i = 0;
	backslashes = 0;
	while (str[i])
	{
		if (str[i] == '&' && (!str[i + 1] || str[i + 1] == ' '))
			backslashes++;
		i++;
	}
	return (backslashes);
}

static	char	*check_single_dollars(char *str)
{
	char	*buff;
	int		j;
	int		i;

	i = -1;
	j = -1;
	if (!(buff = malloc((ft_strlen(str) + count_single_dollars(str))
					* sizeof(char *))))
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '&' && (!str[i + 1] || str[i + 1] == ' '))
			buff[++j] = '\\';
		buff[++j] = str[i];
	}
	buff[++j] = '\0';
	return (buff);
}

/*
** Arg is splitted by $. If any escaped $ is found (\$), the split will be as follows:
** hello$PATH\$PWD -> [hello] [PATH\] [PWD]
** We must then start with the last split and check if previous split ends in '\' in
** order to escape the current env split.
*/

char			*expansion(t_shell *shell, char *str)
{
	char	**env_split;

	str = check_single_dollars(str);
	env_split = ft_split_non_escaped(str, '$');
	if (env_split[0])
	{
		if (env_split[1] || (*env_split[0] != *str))
		{
			free(str);
			str = parse_expansion(shell, env_split, (short)(*str == '$'));
		}
	}
	free(env_split);
	return (str);
	//liberar el resto?
}
