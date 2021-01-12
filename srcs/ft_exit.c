/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:17:27 by migferna          #+#    #+#             */
/*   Updated: 2021/01/12 19:18:57 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_iterate(const char *nptr, long long *num)
{
	while (*nptr >= '0' && *nptr <= '9')
	{
		*num = (*num) * 10 + *nptr - '0';
		nptr++;
	}
}

static	int		exit_atoi(t_shell *shell, const char *nptr)
{
	long long	num;
	int		sign;
	char	*msg;

	sign = 0;
	num = 0;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	if ((*nptr >= 'a' && *nptr <= 'z') || (*nptr >= 'A' && *nptr <= 'Z'))
	{
		msg = ft_strjoin(shell->binary, ": ");
		msg = ft_strjoin(msg, shell->args[1]);
		print_errors(shell, " numeric argument required", msg);
		return (255);
	}
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = 1;
		nptr++;
	}
	if (*nptr == '-' || *nptr == '+')
	{
		msg = ft_strjoin(shell->binary, ": ");
		msg = ft_strjoin(msg, shell->args[1]);
		print_errors(shell, " numeric argument required", msg);
		free(msg);
		return (255);
	}
	if (shell->args[2])
	{
		print_errors(shell, " too many arguments", shell->binary);
		return (1);
	}
	ft_iterate(nptr, &num);
	if (sign == 1)
		num = -1 * num;
	return ((int)num);
}

void			ft_exit(t_shell *shell)
{
	int 	value;
	char	*nbr;

	nbr = shell->args[1];
	if (!nbr)
		value = 0;
	else
		value = exit_atoi(shell, nbr);
	shell->stat_loc = value;
	clean_shell(shell);
	exit(value);
}
