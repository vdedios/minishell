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
