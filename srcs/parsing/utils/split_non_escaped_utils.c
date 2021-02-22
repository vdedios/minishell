/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_non_escaped.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:29:44 by migferna          #+#    #+#             */
/*   Updated: 2021/02/19 19:30:50 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

short	is_delimiter(char input, char delimiter)
{
	if (delimiter == ' ' && is_whitespace(input))
		return (1);
	else if (input == delimiter)
		return (1);
	return (0);
}

int		count_args(char *input, char delimiter)
{
	int		i;
	int		l;

	l = 0;
	i = 0;
	while (input[i])
	{
		if (is_delimiter(input[i], delimiter) && input[i - 1] != '\\')
		{
			l++;
			while (input[i] && !is_delimiter(input[i], delimiter))
				i++;
		}
		i++;
	}
	return (l);
}
