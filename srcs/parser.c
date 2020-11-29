/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:18:25 by migferna          #+#    #+#             */
/*   Updated: 2020/11/09 12:08:36 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_args(char *input)
{
	char **args;

	if (!input)
		return (NULL);
	args = ft_split(input, ' ');
	if (!args)
		return (NULL);
	return (args);
}

char	*parse_input(char *input)
{
	char *tmp;
	char *tmp2;

	tmp2 = parse_backslash(input, 1);
	tmp = parse_quotes(tmp2);
	free (tmp2);
	tmp2 = parse_backslash(tmp, 0);
	free(input);
	free(tmp);
	return (tmp2);
}
