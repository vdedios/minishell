/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 09:03:31 by vde-dios          #+#    #+#             */
/*   Updated: 2020/09/21 10:30:47 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	check_residual_escape(char *str)
{
	if (str[strlen(str) - 1] == '\\')
		str[strlen(str) - 1] = '\0';
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

static	char	*expand_var(char *env, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	check_residual_escape(env);
	while (shell->env[i] && ft_strncmp(shell->env[i], env, ft_strlen(env)))
		i++;
	if (shell->env[i])
		tmp = ft_strdup(shell->env[i]);
	else
		tmp = ft_strdup("");
	free(env);
	return (tmp);
}

static	char	*escape_expansion(char *str)
{
	char	*dollar;
	char	*tmp;

	check_residual_escape(str);
	dollar = ft_strdup("$");
	tmp = ft_strjoin(dollar, str);
	free(str);
	free(dollar);
	return (tmp);
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
		if (len && env_split[len - 1][ft_strlen(env_split[len - 1]) - 1] == '\\')
			env_split[len] = escape_expansion(env_split[len]);
		else if (len || first_is_env)
			env_split[len] = expand_var(env_split[len], shell);
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

void			expansion(t_shell *shell)
{
	int		i;
	char	**env_split;

	i = 1;
	while (shell->args[i])
	{
		env_split = ft_split(shell->args[i], '$');
		if (env_split[1] || (*env_split[0] != *shell->args[i]))
		{
			free(shell->args[i]);
			shell->args[i] = parse_expansion(shell, env_split,
							(short)(*shell->args[i] == '$'));
		}
		free(env_split);
		i++;
	}
}
