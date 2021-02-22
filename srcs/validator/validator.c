/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 16:15:45 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int		validator(t_shell *shell, char *line, char separator, int it)
{
	char	*key;

	if (prior_to_token(line, it - 1, line[it]))
	{
		if (get_validator_err(shell, line, separator, it))
			return (1);
		return (0);
	}
	else if (separator == '|' && nothing_after_pipe(&line[it + 1], it))
	{
		print_errors(shell,
				"line 1: syntax error: unexpected end of file", NULL);
		shell->stat_loc = 2;
		return (1);
	}
	else if ((key = post_to_token(shell, line, it, line[it])))
	{
		safe_print_err(shell, key);
		shell->stat_loc = 1;
		return (1);
	}
	return (0);
}

int		        validate_input(t_shell *shell, char *line)
{
	int it;

	it = -1;
	while (line[++it])
	{
		if (line[it] == '|' ||
			line[it] == '<' ||
			line[it] == '>' ||
			line[it] == ';')
		{
			if (validator(shell, line, line[it], it))
				return (0);
		}
	}
	return (1);
	if (line[it + 1] == '<' || line[it + 1] == '>')
		it++;
}