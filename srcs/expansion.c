/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 09:03:31 by vde-dios          #+#    #+#             */
/*   Updated: 2021/01/19 23:49:42 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		count_keys_to_scape(char *str, char key)
{
	int		backslashes;
	int		i;

	i = 0;
	backslashes = 0;
	while (str[i])
	{
		if ((key == ' ' && str[i] == ' ') ||
			(key == '$' && str[i] == '$' && (!str[i + 1] || str[i + 1] == ' ')))
			backslashes++;
		i++;
	}
	return (backslashes);
}

static	char	*escape_char(char *str, char key)
{
	char	*buff;
	int		j;
	int		i;

	i = -1;
	j = -1;
	if (!(buff = malloc((ft_strlen(str) + count_keys_to_scape(str, key))
					* sizeof(char *))))
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '$' && str[i - 1] != '\\')
		{
			if ((!str[i + 1] || str[i + 1] == ' ')
				|| str[i + 1] == '\\')
			buff[++j] = '\\';
		}
		else if (key != '$' && str[i] == key)
			buff[++j] = '\\';
		buff[++j] = str[i];
	}
	buff[++j] = '\0';
	return (buff);
}

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

static	char	*get_env_value(t_shell *shell, char *delimiter, int i)
{
	char	*ret;
	char	*value;

	if (shell->env[i])
		value = ft_strdup(ft_strchr(shell->env[i], '=') + 1);
	else
		value = ft_strdup("");
	// liberar memoria
	value = escape_char(value, '\\');
	if (delimiter && *(delimiter - 1) == ' ')
		value = escape_char(value, ' ');
	if (delimiter && *delimiter)
	{
		delimiter++;
		ret = ft_strjoin(value, delimiter);
		free(value);
	}
	else
		ret = value;
	return (ret);
}

static	char	*expand_var(char *env, t_shell *shell)
{
	int		i;
	int		len;
	char	*delimiter;

	i = 0;
	env++;
	//free(env);
	//delimiter = search_delimiters(env);
	delimiter = ft_strchr(env, '}');
	len = ft_strlen(env) - (delimiter ? ft_strlen(delimiter) : 0);
	if (delimiter && *(delimiter - 1) == ' ')
		len--;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], env, len)
			&& shell->env[i][len] == '=')
			break;
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

	len = 0;
	buff = ft_strdup("");
	while (env_split[len])
		len++;
	len--;
	while (len >= 0)
	{
		if (env_split[len][1] == '?' && !env_split[len][3])
			env_split[len] = last_proc_status(shell, env_split[len]);
		else if (len || first_is_env)
			env_split[len] = expand_var(env_split[len], shell);
		//liberar desde fuera
		buff = append_expanded(buff, env_split[len]);
		len--;
	}
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
	free(env_split);
	return (str);
	//liberar el resto?
}
