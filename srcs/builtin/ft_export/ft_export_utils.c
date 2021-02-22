/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:45:32 by migferna          #+#    #+#             */
/*   Updated: 2021/02/19 20:16:29 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t  is_bigger(char *s1, char *s2)
{
	int ret;

	ret = 0;
	if (*s1 == *s2)
		ret = is_bigger(s1 + 1, s2 + 1);
	else if (*s1 > *s2)
		ret = 1;
	return (ret);
}

char	**sort_alpha(char **envp)
{
	char	*tmp;
	size_t	len;
	size_t	i;
	size_t	j;

	len = 0;
	i = 0;
	while (envp[len + 1])
		len++;
	while (i < len)
	{
		j = 0;
		while (j < len - i)
		{
			if (is_bigger(envp[j], envp[j + 1]))
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

short	is_escapable_char_export(char c)
{
	if (c == '$' || c == '\\' || c == '\"')
		return (1);
	return (0);
}

int		count_special_chars(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		if (is_escapable_char_export(*str))
			count++;
		str++;
	}
	return (count);
}

char	*add_quotes_and_backslash(char *str)
{
	char	*buff;
	int		i;

	i = 0;
	if (!(buff = malloc((ft_strlen(str) + count_special_chars(str) + 3)
						* sizeof(char))))
		return (NULL);
	while (*str)
	{
		if (is_escapable_char_export(*str))
			buff[i++] = '\\';
		buff[i++] = *str;
		if (*str == '=')
			buff[i++] = '\"';
		str++;
	}
	buff[i++] = '\"';
	buff[i] = '\0';
	return (buff);
}
