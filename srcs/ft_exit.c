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

static	void	numeric_arg_req(t_shell *shell)
{
	char		*msg;

	msg = ft_strjoin(shell->binary, ": ");
	msg = ft_strjoin(msg, shell->args[1]);
	print_errors(shell, " numeric argument required", msg);
	exit (255);
}

static	int		exit_atoi(t_shell *shell, const char *nptr)
{
	uintmax_t	num;
	int			sign;

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
		if ((!ft_isdigit(*nptr) && *nptr != ' ' && *nptr != '\t')
		|| ft_strlen(nptr) > 19)
			numeric_arg_req(shell);
		if (*nptr >= '0' && *nptr <= '9')
			num = num * 10 + *nptr - '0';
		nptr++;
	}
	if ((!sign && num > INTMAX_MAX) || (sign && num > (uintmax_t)(-INTMAX_MIN)))
		numeric_arg_req(shell);
	if (sign == 1)
		num = -1 * num;
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