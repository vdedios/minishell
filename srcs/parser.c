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

/*
** ft_split_args behaves similarly like ft_split with space
** as a delimiter, and only considering it as valid if not 
** escaped.
*/

char			**get_args(char *input)
{
	char **args;

	if (!input)
		return (NULL);
	args = ft_split_args(input);
	free(input);
	if (!args)
		return (NULL);
	return (args);
}

char			*parse_input(char *input)
{
	char *tmp;
	char *tmp2;

	tmp = parse_quotes(input);
	tmp2 = parse_backslash(tmp, 0);
	free (tmp);
	free(input);
	return (tmp2);
}
