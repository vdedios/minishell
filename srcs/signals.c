/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:17:38 by migferna          #+#    #+#             */
/*   Updated: 2020/09/17 11:21:00 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_running(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n$:\\>", 1);
	signal(SIGINT, signal_handler_running);
	signal(SIGQUIT, signal_handler_running);
}

void	signal_handler_waiting(int sig)
{
	(void)sig;
	signal(SIGINT, signal_handler_waiting);
}
