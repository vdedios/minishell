/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:18:25 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 16:07:56 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_residual_backslash(char **args)
{
	char	*tmp;
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
	if (!args)
		return (NULL);
	return (args);
}

char			*parse_input(char *input)
{
	char *tmp;
	char *buff;

	tmp = parse_quotes(input);
	if (tmp)
	{
		buff = parse_backslash(tmp, 0);
		free(tmp);
	}
	else
		buff = NULL;
	return (buff);
}
