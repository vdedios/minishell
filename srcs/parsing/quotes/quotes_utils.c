/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:00:26 by migferna          #+#    #+#             */
/*   Updated: 2021/02/19 19:00:41 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	check_prev_backslashes(char *str, int i)
{
	int n;

	n = 0;
	while (i && str[--i] == '\\')
		n++;
	return ((n + 1) % 2);
}

short	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

short	is_special_char(char c)
{
	if (c == '$' || c == '\\' || c == '|' || c == ';' || c == '\'')
		return (1);
	return (0);
}

short	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		n_special_chars(char *str, int opening, int closing, char quote)
{
	int	i;
	int	n;

	i = opening + 1;
	n = 0;
	while (i < closing)
	{
		if (quote != '\'' && is_special_char(str[i]))
			n++;
		else if (is_space(str[i]))
			n++;
		i++;
	}
	return (n);
}
