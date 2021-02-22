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

char	*last_arg(char *arg)
{
	char	*buff;

	if ((buff = ft_strchr(arg, '=')))
		*buff = '\0';
	return (ft_strjoin("_=", arg));
}

char	*update_last_arg(char **args)
{
	int len;

	len = 0;
	while (args[len])
		len++;
	return (last_arg(args[len - 1]));
}

char	*append_pwd(char *value)
{
	char	cwd[1024];
	char	*aux;

	aux = value;
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (value[0] == ':')
			return (ft_strjoin(cwd, value));
		if (value[ft_strlen(value) - 1] == ':')
			return (ft_strjoin(value, cwd));
		while (*aux)
		{
			if (!(aux = ft_strchr(aux, ':')))
				break ;
			if (*(aux + 1) == ':')
				return (ft_strjoin(value, cwd));
			aux++;
		}
	}
	return (ft_strdup(value));
}

char	*to_lower(char *input)
{
	size_t	it;
	char	*output;
	char	*tmp;

	tmp = ft_strdup(input);
	output = calloc(1, ft_strlen(tmp));
	it = -1;
	while (tmp[++it])
	{
		output[it] = ft_tolower(tmp[it]);
	}
	free(tmp);
	output[it] = '\0';
	return (output);
}

char	*safe_allocate(char *line, char *(*f)(char *))
{
	char	*tmp;
	char	*aux;

	tmp = f(line);
	free(line);
	aux = ft_strdup(tmp);
	free(tmp);
	return (aux);
}
