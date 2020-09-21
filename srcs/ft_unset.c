/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:14:51 by migferna          #+#    #+#             */
/*   Updated: 2020/09/12 13:52:18 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset(char *var, char **env)
{
	size_t	it;
	size_t	len;

	len = ft_strlen(var);
	it = 0;
	while (env[it])
	{
		if (ft_strncmp(var, env[it], len) == 0)
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
		env[it] = NULL;
	}
	return (1);
}
