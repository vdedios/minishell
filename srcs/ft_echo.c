/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:03:29 by migferna          #+#    #+#             */
/*   Updated: 2021/02/18 18:57:32 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args)
{
	int		end;
	size_t	it;

	it = 0;
	end = 1;
	while (args[it])
	{
		if (ft_strncmp(args[it], "-n", 2) == 0)
		{
			end = 0;
			it++;
		}
		else
			break ;
	}
	while (args[it])
	{
		ft_putstr_fd(args[it], 1);
		if (args[it + 1])
			write(1, " ", 1);
		it++;
	}
	if (end)
		write(1, "\n", 1);
	return (1);
}
