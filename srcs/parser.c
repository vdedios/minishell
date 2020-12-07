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

static	void	move_backwards_args(char **args, int i)
{
	i++;
	while (args[i])
	{
		args[i]	= args[i + 1];
		i++;
	}
}

static	short	check_escaped_spaces(char **args)
{
	char 	*tmp;
	char	*tmp2;
	int		len;
	int		i;

	i = 0;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		if (args[i][len - 1] == '\\')
		{
			if (!((tmp = malloc((len) * sizeof(char)))))
				return (0);
			ft_strlcpy(tmp, args[i], len);
			if (args[i + 1])
			{
				tmp2 = ft_strjoin(tmp, " ");
				free(tmp);
				tmp = ft_strjoin(tmp2, args[i + 1]);
			free(tmp2);
			}
			free(args[i]);
			args[i] = tmp;
			move_backwards_args(args, i);
		}
		else
			i++;
	}
	return (1);
}

char			**get_args(char *input)
{
	char **args;

	if (!input)
		return (NULL);
	args = ft_split(input, ' ');
	check_escaped_spaces(args);
	if (!args)
		return (NULL);
	return (args);
}

char			*parse_input(char *input)
{
	char *tmp;
	char *tmp2;

	tmp = parse_quotes(input);
	tmp2 = parse_backslash(tmp);
	free (tmp);
	free(input);
	return (tmp2);
}
