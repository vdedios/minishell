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

char	*add_space(char *line, char *output, size_t *it, char redir)
{
	if (line[*it] == redir)
	{
		ft_strlcat(output, line, ft_strlen(output) + *it + 1);
		if (line[*it - 1] != ' ' && line[*it - 1] != redir)
			ft_strlcat(output, " ", ft_strlen(output) + 2);
		ft_strlcat(output, line + *it, ft_strlen(output) + 2);
		if (line[*it + 1] != ' ' && line[*it + 1] != redir)
			ft_strlcat(output, " ", ft_strlen(output) + 2);
		line = line + *it + 1;
		*it = -1;
	}
	return (line);
}

size_t	additional_spaces(char *line)
{
	size_t	cont;
	size_t	it;

	it = -1;
	cont = 0;
	while (line[++it])
	{
		if (line[it] == '>' && line[it - 1] != ' ' && line[it - 1] != '>')
			cont++;
		if (line[it] == '>' && line[it + 1] != ' ')
			cont++;
		if (line[it] == '<' && line[it - 1] != ' ' && line[it - 1] != '<')
			cont++;
		if (line[it] == '<' && line[it + 1] != ' ')
			cont++;
	}
	return (cont);
}

char	*inject_spaces(char *line)
{
	size_t	it;
	size_t	cont;
	char	*output;

	it = -1;
	cont = additional_spaces(line);
	output = calloc(1, ft_strlen(line) + cont + 1);
	while (*line == ' ')
		line++;
	while (line[++it])
	{
		line = add_space(line, output, &it, '>');
		line = add_space(line, output, &it, '<');
	}
	ft_strlcat(output, line, line - output);
	return (output);
}
