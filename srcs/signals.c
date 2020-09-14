/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:17:38 by migferna          #+#    #+#             */
/*   Updated: 2020/09/14 13:10:11 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	ft_putendl_fd("\nCaught signal", 1);
	ft_putnbr_fd(signal, 1);
	exit(0);
}
