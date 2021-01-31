/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:14:51 by migferna          #+#    #+#             */
/*   Updated: 2021/01/17 23:19:00 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_environment(t_shell *shell, char	*key, char **env)
{
	size_t	it;
	size_t	len;
	char	*msg;

	len = ft_strlen(key);
	it = 0;
	while (env[it])
	{
		if (ft_strncmp(key, env[it], len) == 0)
			break ;
		it++;
	}
	if (env[it])
	{
		env[it] = NULL;
		it++;
		while (env[it])
		{
			env[it - 1] = env[it];
			it++;
		}
		env[it - 1] = NULL;
	}
}

static short	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static short	is_forbidden_char(char *str, int i)
{
	if (str[i] == ' ' ||
		str[i] == '\'' ||
		str[i] == '\"' ||
		str[i] == '$' ||
		str[i] == '!' ||
		str[i] == '|' ||
		str[i] == ';' ||
		str[i] == '&' ||
		str[i] == '@')
		return (1);
	else if(str[i] == '\\' &&
			(str[i + 1] != '_' && !is_num(str[i + 1])))
		return (1);
	return (0);
}

static short	has_valid_name(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (is_forbidden_char(str, i))
			return (0);
		i++;
	}
	if (str[i] == '=' && !str[i + 1])
		return (0);
	return (1);
}

static	short	not_valid_keyname(t_shell *shell, char *var)
{
	char	*err_mssg;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(var);
	if (!(err_mssg = malloc((len + 28) * sizeof(char))))
		return (0);
	ft_strlcpy(err_mssg, " `", 3);
	ft_strlcpy(err_mssg + 2, var, len + 1);
	ft_strlcpy(err_mssg + 2 + len, "': not a valid identifier", 26);
	shell->stat_loc = 1;
	print_errors(shell, err_mssg, "unset");
	free(err_mssg);
	return (1);
}

int		ft_unset(t_shell *shell)
{
	size_t	it;

	it = 1;
	while (shell->args[it])
	{
		if (has_valid_name(shell->args[it]))
			delete_environment(shell, shell->args[it], shell->env);
		else
			not_valid_keyname(shell, shell->args[it]);
		it++;
	}
	return (1);
}
