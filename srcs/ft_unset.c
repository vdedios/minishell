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
	else
	{
		msg = ft_strjoin(shell->binary, ": `");
		msg = ft_strjoin(msg, key);
		msg = ft_strjoin(msg, "'");
		print_errors(shell, " not a valid identifier", msg);
		shell->stat_loc = 1;
	}
}

int		ft_unset(t_shell *shell)
{
	size_t	it;

	it = 1;
	while (shell->args[it])
	{
		delete_environment(shell, shell->args[it], shell->env);
		it++;
	}
	return (1);
}
