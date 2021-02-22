/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:54:38 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 17:14:46 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_in_quotes(char *str, char quote, int opening, int closing)
{
	char *buff;

	if (!(buff = malloc((closing - opening
		+ n_special_chars(str, opening, closing, quote) + 1)
		* sizeof(char))))
		return (NULL);
	return (buff);
}

char	*get_string_between_quotes(char *str, int opening,
										int closing, char quote)
{
	char	*buff;
	int		i;
	int		j;

	j = 0;
	i = opening + 1;
	buff = alloc_in_quotes(str, quote, opening, closing);
	while (i < closing)
	{
		if (quote == '\'' && (is_special_char(str[i]) ||
			(str[i - 1] == '\\' && is_alpha(str[i]))))
			buff[j++] = '\\';
		else
		{
			if (is_space(str[i])
				|| str[i] == '|' || str[i] == ';' || str[i] == '\'')
				buff[j++] = '\\';
			if (str[i - 1] == '\\' && (str[i] == '|' || is_alpha(str[i])))
				buff[j++] = '\\';
		}
		buff[j++] = str[i++];
	}
	buff[j] = '\0';
	return (buff);
}

void	handle_quote_error(char quote)
{
	if (quote == '\'')
		print_errors(NULL
			, "unexpected EOF while looking for matching `''", NULL);
	else
		print_errors(NULL
			, "unexpected EOF while looking for matching `\"'", NULL);
}

char	*find_closing_quote(char *str, char quote
								, int opening, int *closing)
{
	int	i;

	i = opening + 1;
	*closing = 0;
	if (str[i] == quote && i >= 2 && str[i - 2] == ' ')
	{
		*closing += opening + 1;
		return (ft_strdup("\"\" "));
	}
	while (str[i])
	{
		if (str[i] == quote
			&& (quote == '\'' || check_prev_backslashes(str, i)))
		{
			*closing += opening + 1;
			return (get_string_between_quotes(str, opening
						, *closing, quote));
		}
		*closing += 1;
		i++;
	}
	handle_quote_error(quote);
	return (NULL);
}
