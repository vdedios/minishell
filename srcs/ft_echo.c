/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:03:29 by migferna          #+#    #+#             */
/*   Updated: 2020/12/07 20:08:13 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_all_characters(char* str, char c)
{
	size_t	cont;	

	cont = 0;
	while (*str)
	{
		if (*str == c)
			cont++;
		str++;
	}
	return (cont);
	
}

static char	*clean(char *str, char *blacklist)
{
	char	*str_clean;
	char	*tmp;
	size_t	len_orig;
	size_t	cont;
	
	len_orig = ft_strlen(str);
	cont = find_all_characters(str, *blacklist);
	str_clean = ft_calloc(sizeof(char), len_orig - cont);
	tmp = str_clean;
	while (*str)
	{
		if (*str != *blacklist)
		{
			*str_clean = *str;
			str_clean++;
		}
		str++;
	}
	return (tmp);
}

int		ft_echo(char **args)
{
	int		end;
	char	*tmp;
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
		tmp = clean(*args, "\\");
		ft_putstr_fd(args[it], 1);
		if (args[it+1])
			write(1, " ", 1);
		free(tmp);
		it++;
	}
	if (end)
		write(1, "\n", 1);
	return (1);
}