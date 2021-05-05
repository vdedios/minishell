/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:17:38 by migferna          #+#    #+#             */
/*   Updated: 2020/10/24 18:32:32 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_running(int sig)
{
	if (sig == SIGINT)
	{
		//ft_putstr_fd("\033[2D\033[J\n", 1);
		ft_putstr_fd("\033[H\033[J\n", 1);
		signal(SIGINT, signal_handler_running);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("\033[2D\033[J", 1);
		signal(SIGQUIT, signal_handler_running);
	}
}

void	signal_handler_waiting(int sig)
{
	(void)sig;
	signal(SIGINT, signal_handler_waiting);
}
