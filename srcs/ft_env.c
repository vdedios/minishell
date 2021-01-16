/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:15:33 by migferna          #+#    #+#             */
/*   Updated: 2021/01/16 00:49:36 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_shell *shell, char *arg)
{
	size_t it;
	size_t len;

	len = ft_strlen(arg);
	it = 0;
	while (shell->env[it])
	{
		if (!ft_strncmp(shell->env[it], arg, len))
			return (ft_strchr(shell->env[it], '=') + 1);
		it++;
	}
	return (NULL);
}

int	ft_env(t_shell *shell, char **args)
{
	size_t it;
	char	*path;
	int		*binary;

	binary = NULL;
	(void)args;
	path = get_path(shell, binary);
	ft_export(shell, ft_strjoin("_=", path));
	if (shell->args[1])
	{
		ft_putendl_fd("env: too many arguments", 1);
		return (1);
	}
	it = 0;
	while (shell->env[it])
		ft_putendl_fd(shell->env[it++], 1);
	return (1);
}
