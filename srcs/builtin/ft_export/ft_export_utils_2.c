/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:45:32 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 22:32:56 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strncmp_equal(char *str1, char *str2, int len)
{
	while (*str1 && *str2 && len)
	{
		if (*str1 != *str2)
			return (1);
		str1++;
		str2++;
		len--;
	}
	if (*str1 == *str2)
		return (0);
	return (1);
}

short	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

short	is_forbidden_char(char *str, int i)
{
	if (str[i] == '$' ||
		str[i] == '&' ||
		str[i] == '|' ||
		str[i] == '@' ||
		str[i] == ';' ||
		str[i] == '!' ||
		str[i] == ' ' ||
		str[i] == '\"' ||
		str[i] == '\'')
		return (1);
	else if (str[i] == '\\' &&
			(str[i + 1] != '_' && !is_num(str[i + 1])))
		return (1);
	return (0);
}

short	has_valid_name(char *str)
{
	int	i;

	i = 0;
	if (!*str || is_num(*str) || *str == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (is_forbidden_char(str, i))
			return (0);
		i++;
	}
	return (1);
}

short	not_valid_keyname(t_shell *shell, char *var, char *command)
{
	char	*err_mssg;
	int		len;

	len = ft_strlen(var);
	if (!(err_mssg = malloc((len + 28) * sizeof(char))))
		return (0);
	ft_strlcpy(err_mssg, " `", 3);
	ft_strlcpy(err_mssg + 2, var, len + 1);
	ft_strlcpy(err_mssg + 2 + len, "': not a valid identifier", 26);
	shell->stat_loc = 1;
	print_errors(shell, err_mssg, command);
	free(err_mssg);
	return (1);
}
