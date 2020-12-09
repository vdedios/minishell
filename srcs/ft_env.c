/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:15:33 by migferna          #+#    #+#             */
/*   Updated: 2020/10/24 19:26:00 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, char **env)
{
	size_t it;

	if (args[0])
	{
		ft_putendl_fd("env: too many arguments", 1);
		return (1);
	}
	it = 0;
	while (env[it])
		ft_putendl_fd(env[it++], 1);
	return (1);
}
