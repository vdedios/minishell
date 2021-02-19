/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:39:07 by migferna          #+#    #+#             */
/*   Updated: 2021/02/18 22:45:55 by migferna         ###   ########.fr       */
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

static short	is_limit_character(char character)
{
	if (character == '\'' || character == '\"' ||
			character == '\\' ||
			character == ',' ||
			character == '[' ||
			character == ']' ||
			character == '$' ||
			character == ' ' ||
			character == '@' ||
			character == ';' ||
			character == '\0')
		return (1);
	return (0);
}

char			*set_opening_braces(char *str)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(buff = malloc((ft_strlen(str) + count_chars(str, '$') + 1) *
					sizeof(char))))
		return (NULL);
	while (str[j])
	{
		if (j - 1 >= 0 && str[j - 1] == '$' &&
				(j - 2 < 0 || str[j - 2] != '\\') &&
				str[j] != '\\' && str[j] != '%')
			buff[i++] = '{';
		buff[i++] = str[j++];
	}
	buff[i] = '\0';
	return (buff);
}

char			*set_closing_braces(char *str)
{
	short	is_open_brace;
	char	*buff;
	int		i;
	int		k;

	i = 0;
	k = 0;
	is_open_brace = 0;
	if (!(buff = malloc((ft_strlen(str) + count_chars(str, '{') + 3) *
					sizeof(char))))
		return (NULL);
	while (str[k])
	{
		if (str[k] == '{' && (k - 1) >= 0 && str[k - 1] == '$')
			is_open_brace = 1;
		buff[i++] = str[k];
		if (is_open_brace && is_limit_character(str[k + 1]))
		{
			buff[i++] = '}';
			is_open_brace = 0;
		}
		k++;
	}
	buff[i] = '\0';
	return (buff);
}
