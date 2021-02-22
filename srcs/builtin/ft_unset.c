/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:14:51 by migferna          #+#    #+#             */
/*   Updated: 2021/02/18 18:54:49 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static short	has_valid_name_unset(char *str)
{
	int	i;

	i = 0;
	if (!*str || is_num(*str) || *str == '=')
		return (0);
	while (str[i])
	{
		if (is_forbidden_char(str, i) || str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int				ft_unset(t_shell *shell)
{
	size_t	it;

	it = 1;
	while (shell->args[it])
	{
		if (has_valid_name_unset(shell->args[it]))
			delete_environment(shell, shell->args[it], shell->env);
		else
			not_valid_keyname(shell, shell->args[it], "unset");
		it++;
	}
	return (1);
}
