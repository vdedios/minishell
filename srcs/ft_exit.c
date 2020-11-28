/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:17:27 by migferna          #+#    #+#             */
/*   Updated: 2020/11/28 11:58:47 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_iterate(const char *nptr, long long *num)
{
	while (*nptr >= '0' && *nptr <= '9')
	{
		*num = (*num) * 10 + *nptr - '0';
		nptr++;
	}
}

static	int		exit_atoi(const char *nptr)
{
	long long	num;
	int		sign;

	sign = 0;
	num = 0;
	while (*nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r' || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = 1;
		nptr++;
	}
	ft_iterate(nptr, &num);
	if (sign == 1)
		num = -1 * num;
	return ((int)num);
}
void	ft_exit(t_shell *shell)
{
	int 	value;
	char	*nbr;

	nbr = shell->args[1];
	if (!nbr)
		value = 0;
	else
		value = exit_atoi(nbr);
	shell->stat_loc = value;
	clean_shell(shell);
	exit(value);
}
