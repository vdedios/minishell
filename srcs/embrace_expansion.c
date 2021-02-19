/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   embrace_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:18:03 by migferna          #+#    #+#             */
/*   Updated: 2021/02/18 22:46:27 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_chars(char *str, char character)
{
	int l;

	l = 0;
	while (*str)
	{
		if (*str == character)
			l++;
		str++;
	}
	return (l);
}

char			*mantain_expansion_spaces(char *str)
{
	int		i;
	short	var_opened;
	char	*buff;

	i = 0;
	var_opened = 0;
	if (!(buff = malloc((ft_strlen(str) + count_chars(str, '$') + 1) *
					sizeof(char))))
		return (NULL);
	while (*str)
	{
		if (*str == '$' && *(str - 1) != '\\' && !var_opened)
			var_opened = 1;
		buff[i++] = *str;
		if (var_opened && *(str + 1) == '}')
		{
			var_opened = 0;
			buff[i++] = ' ';
		}
		str++;
	}
	buff[i] = '\0';
	return (buff);
}

char			*embrace_expansion(char *str)
{
	char	*buff;
	char	*tmp;

	tmp = set_opening_braces(str);
	buff = set_closing_braces(tmp);
	free(tmp);
	return (buff);
}
