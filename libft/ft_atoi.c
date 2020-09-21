/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:31:17 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/19 13:23:27 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** convert a char to int with the following format:
** isspace(as many as you want) + one sign + numbers
** anything else it returns a 0
*/

#include "libft.h"

static void	ft_iterate(const char *nptr, long double *num)
{
	while (*nptr >= '0' && *nptr <= '9')
	{
		*num = (*num) * 10 + *nptr - '0';
		nptr++;
	}
}

int		ft_atoi(const char *nptr)
{
	long double	num;
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
	if (num > 2147483647)
		return (-1);
	if (num < -2147483648)
		return (0);
	return ((int)num);
}
