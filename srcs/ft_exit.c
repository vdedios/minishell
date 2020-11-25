/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:17:27 by migferna          #+#    #+#             */
/*   Updated: 2020/11/23 19:21:34 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	int value;

	if (!shell->args[1])
		value = 0;
	else
		value = ft_atoi(shell->args[1]);
	shell->stat_loc = value;
	clean_shell(shell);
	//kill(0, SIGTERM);
	exit(value);
}
