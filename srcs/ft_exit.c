/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:17:27 by migferna          #+#    #+#             */
/*   Updated: 2021/01/16 19:38:47 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		exit_atoi(t_shell *shell, const char *nptr)
{
	long long	num;
	int		sign;
	char	*msg;

	num = 0;
	sign = 0;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = 1;
		nptr++;
	}
	while (*nptr == '0')
		nptr++;
	while (*nptr)
	{
		if ((!ft_isdigit(*nptr) && *nptr != ' ' && *nptr != '\t') || ft_strlen(nptr) >= 19)
		{
			msg = ft_strjoin(shell->binary, ": ");
			msg = ft_strjoin(msg, shell->args[1]);
			print_errors(shell, " numeric argument required", msg);
			exit (255);
		}
		if (*nptr >= '0' && *nptr <= '9')
			num = num * 10 + *nptr - '0';
		nptr++;
	}

	if (sign == 1)
		num = -1 * num;
	/*if ((*nptr >= 'a' && *nptr <= 'z') || (*nptr >= 'A' && *nptr <= 'Z'))
	{
		msg = ft_strjoin(shell->binary, ": ");
		msg = ft_strjoin(msg, shell->args[1]);
		print_errors(shell, " numeric argument required", msg);
		return (255);
	}*/
	//if (sign == 1)
	//	num = -1 * num;
	return ((int)num);
}

void			ft_exit(t_shell *shell)
{
	int 	value;
	char	*nbr;

	if (shell->args[1])
	{
		nbr = shell->args[1];
		value = exit_atoi(shell, nbr);
		if (shell->args[2])
		{
			print_errors(shell, " too many arguments", shell->binary);
			exit(1);
		}
	}
	else
		value = 0;
	shell->stat_loc = value;
	clean_shell(shell);
	exit(value);
}
