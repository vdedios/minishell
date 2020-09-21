/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:03:29 by migferna          #+#    #+#             */
/*   Updated: 2020/09/18 09:21:27 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args)
{
	int		end;
	size_t	len;
	size_t	it;

	it = 0;
	end = 1;
	if (*args && (*args)[it++] == '-' && (*args++)[it] == 'n')
		end = 0;
	while (*args)
	{
		len = ft_strlen(*args);
		write(1, *args++, len);
		if (*args)
			write(1, " ", 1);
	}
	if (end)
		write(1, "\n", 1);
	return (1);
}
