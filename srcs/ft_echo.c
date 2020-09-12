/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:03:29 by migferna          #+#    #+#             */
/*   Updated: 2020/09/12 10:03:34 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args)
{
	char	*end;
	size_t	len;
	size_t	it;

	end = ft_strdup("\n");
	it = 0;
	if (*args && (*args)[it++] == '-' && (*args++)[it] == 'n')
		end = NULL;
	while (*args)
	{
		len = ft_strlen(*args);
		write(1, *args++, len);
		if (*args)
			write(1, " ", 1);
	}
	if (end)
	{
		write(1, end, 1);
		free(end);
	}
	return (1);
}
