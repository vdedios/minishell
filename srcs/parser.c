/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:18:25 by migferna          #+#    #+#             */
/*   Updated: 2021/02/15 18:07:53 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_split_args behaves similarly like ft_split with space
** as a delimiter, and only considering it as valid if not 
** escaped.
*/

static	void	delete_residual_backslash(char **args)
{
	char *tmp;
	size_t	it;

	it = -1;
	while (args[++it])
	{
		tmp = parse_backslash(args[it], 1);
		free(args[it]);
		args[it] = ft_strdup(tmp);
		free(tmp);
	}
}

char			**get_args(char *input)
{
	char **args;

	if (!input)
		return (NULL);
	args = ft_split_non_escaped(input, ' ');
	delete_residual_backslash(args);
	//free(input);
	if (!args)
		return (NULL);
	return (args);
}

char			*parse_input(char *input)
{
	char *tmp;
	char *buff;

	tmp = parse_quotes(input);
	buff = parse_backslash(tmp, 0);
	free (tmp);
	//free(input);
	return (buff);
}
