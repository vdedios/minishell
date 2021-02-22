/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 09:03:31 by vde-dios          #+#    #+#             */
/*   Updated: 2021/02/22 22:29:19 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_keys_to_scape(char *str, char key)
{
	int		backslashes;
	int		i;

	i = 0;
	backslashes = 0;
	while (str[i])
	{
		if ((key == ' ' && str[i] == ' ') ||
			(key == '$' && str[i] == '$' &&
			((!str[i + 1] || str[i + 1] == ' ') ||
			str[i + 1] == '%')))
			backslashes++;
		i++;
	}
	return (backslashes);
}

char	*escape_char(char *str, char key)
{
	char	*buff;
	int		j;
	int		i;

	i = -1;
	j = -1;
	if (!(buff = malloc((ft_strlen(str) + count_keys_to_scape(str, key))
					* sizeof(char *))))
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '$' && str[i - 1] != '\\')
		{
			if (!str[i + 1] ||
				str[i + 1] == ' ' ||
				str[i + 1] == '\\' ||
				str[i + 1] == '%')
				buff[++j] = '\\';
		}
		else if (key != '$' && str[i] == key)
			buff[++j] = '\\';
		buff[++j] = str[i];
	}
	buff[++j] = '\0';
	return (buff);
}

char	*append_expanded(char *buff, char *env)
{
	char	*tmp;

	if (*env == '\\' && !(*(env + 1)))
		return (buff);
	tmp = ft_strjoin(env, buff);
	return (tmp);
}

void	escape_char_safe(char **value, char c)
{
	char	*tmp;

	tmp = ft_strdup(*value);
	free(*value);
	*value = escape_char(tmp, c);
	free(tmp);
}
