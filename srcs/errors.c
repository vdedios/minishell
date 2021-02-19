/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:22:01 by migferna          #+#    #+#             */
/*   Updated: 2021/02/18 18:22:29 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_errors(t_shell *shell, char *msg, char *bin)
{
	(void)shell;
	ft_putstr_fd("minishell: ", 2);
	if (bin)
	{
		ft_putstr_fd(bin, 2);
		ft_putchar_fd(':', 2);
	}
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
