/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 21:35:35 by migferna          #+#    #+#             */
/*   Updated: 2021/02/19 21:35:36 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

char	*add_char(char *line, char buffer)
{
	char	*output;
	int		l;

	l = 0;
	while (line && line[l])
		l++;
	if (!(output = malloc((l + 2) * sizeof(char))))
		return (NULL);
	l = 0;
	while (line && line[l])
	{
		output[l] = line[l];
		l++;
	}
	output[l] = buffer;
	output[l + 1] = '\0';
	free(line);
	return (output);
}

int		get_next_line(char **line)
{
	int		output;
	char	buffer;

	if (!(*line = malloc(sizeof(char))))
		return (-1);
	**line = '\0';
	buffer = 0;
	output = 1;
	while (output || buffer)
	{
		if ((output = read(0, &buffer, 1)) == -1)
			return (-1);
		if (buffer == '\n')
			break ;
		if (!(*line = add_char(*line, buffer)))
			return (-1);
	}
	return (output);
}
