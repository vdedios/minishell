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

static char	*remove_quotes(char *str, int *opening, int *closing)
{
	char	quote;

	*opening = 0;
	while (str[*opening])
	{
		if ((str[*opening] == '\'' || str[*opening] == '\"')
			&& check_prev_backslashes(str, *opening))
		{
			quote = str[*opening];
			return (find_closing_quote(str, quote, *opening, closing));
		}
		*opening += 1;
	}
	*opening = -1;
	return (str);
}

static char	*join_prev_in_quotes(char *str, char *buff,
									char *tmp_in_quotes, int opening)
{
	char	*str_pre_quotes;
	char	*tmp_pre_quotes;
	char	*tmp;
	char	*tmp2;

	if (!(str_pre_quotes = malloc((opening + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(str_pre_quotes, str, opening + 1);
	tmp_pre_quotes = embrace_expansion(str_pre_quotes);
	tmp = ft_strjoin(buff, tmp_pre_quotes);
	tmp2 = ft_strjoin(tmp, tmp_in_quotes);
	free(tmp_pre_quotes);
	free(str_pre_quotes);
	free(tmp);
	return (tmp2);
}

static char	*join_parsed_str(char *str, char *str_in_quotes,
								char *buff, int opening)
{
	char	*tmp_in_quotes;
	char	*tmp;

	tmp_in_quotes = embrace_expansion(str_in_quotes);
	if (opening != -1)
	{
		tmp = mantain_expansion_spaces(tmp_in_quotes);
		free(tmp_in_quotes);
		tmp_in_quotes = ft_strdup(tmp);
		free(tmp);
	}
	if (opening && opening != -1)
		tmp = join_prev_in_quotes(str, buff,
									tmp_in_quotes, opening);
	else
	{
		if (ft_strcmp(buff, ""))
			tmp = ft_strdup(tmp_in_quotes);
		else
			tmp = ft_strjoin(buff, tmp_in_quotes);
	}
	free(tmp_in_quotes);
	return (tmp);
}

char		*parse_quotes(char *str)
{
	char	*str_in_quotes;
	char	*buff;
	char	*tmp;
	int		opening;
	int		closing;

	buff = ft_strdup("");
	while (*str)
	{
		if (!(str_in_quotes = remove_quotes(str, &opening, &closing)))
		{
			free(buff);
			return (NULL);
		}
		tmp = join_parsed_str(str, str_in_quotes, buff, opening);
		free(buff);
		buff = tmp;
		if (str_in_quotes != str)
			free(str_in_quotes);
		if (opening != -1)
			str += (closing + 1);
		else
			break ;
	}
	return (buff);
}
