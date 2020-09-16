/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:17:38 by migferna          #+#    #+#             */
/*   Updated: 2020/09/16 20:05:28 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_parent(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n$:\\>", 1);
		signal(sig, signal_handler_parent);
	}
}

void	signal_handlerd_parent(int sig)
{
	if (sig == SIGQUIT)
		signal(SIGINT, signal_handlerd_parent);
}

void	signal_handlerd_children(int sig)
{
	if (sig == SIGQUIT)
		signal(SIGINT, signal_handlerd_children);
}

void	signal_handler_children(int sig)
{
	if (sig == SIGINT)
		signal(sig, signal_handler_children);
}
