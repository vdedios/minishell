/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:31:17 by vde-dios          #+#    #+#             */
/*   Updated: 2020/12/23 19:13:12 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** convert a char to int with the following format:
** isspace(as many as you want) + one sign + numbers
** anything else it returns a 0
*/

#include "libft.h"
#include <limits.h>

long int			ft_atoi(const char *str)
{
	long double			res;
	int					sign;
	unsigned int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	//printf("NUM: %ld", (long int)res * sign);
	return ((long double)(res * sign));
}
