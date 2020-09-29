/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:03:29 by migferna          #+#    #+#             */
/*   Updated: 2020/09/29 13:13:13 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_all_characters(char* str, char c)
{
	size_t	len;
	size_t	cont;	

	cont = 0;
	len = 0;
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
	size_t	len;
	size_t	it;
	char	*tmp;

	it = 0;
	end = 1;
	if (*args && (*args)[it++] == '-' && (*args++)[it] == 'n')
		end = 0;
	while (*args)
	{
		tmp = clean(*args, "\\");
		len = ft_strlen(tmp);
		write(1, tmp, len);
		args++;
		if (*args)
			write(1, " ", 1);
	}
	free(tmp);
	if (end)
		write(1, "\n", 1);
	return (1);
}
