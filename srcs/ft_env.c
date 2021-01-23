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

static	void	sort_like_bash(char **env)
{
	size_t	it;
	char	*aux;

	it = 0;
	while (env[it])
	{
		if (!ft_strncmp(env[it], "PATH=", 5))
		{
			aux = env[it];
			env[it] = env[it + 1];
			env[it + 1] = aux;
			it++;
		}
		it++;
	}
}

int	ft_env(t_shell *shell, char **args)
{
	size_t	it;
	char	**to_print_env;

	if (shell->args[1])
	{
		ft_putendl_fd("env: too many arguments", 1);
		return (1);
	}
	it = 0;
	to_print_env = args;
	sort_like_bash(to_print_env);
	while (to_print_env[it])
		ft_putendl_fd(to_print_env[it++], 1);
	return (1);
}