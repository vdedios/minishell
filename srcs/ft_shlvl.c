/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:36:17 by migferna          #+#    #+#             */
/*   Updated: 2021/02/14 15:34:56 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_shlvl(t_shell *shell)
{
	char					*shlvl;
	int						lvl;
	char					*msg;
	char					*tmp;

	shlvl = get_env(shell, "SHLVL=");
	if (!shlvl)
		shlvl = "0";
	lvl = (int)ft_atoi(shlvl) + 1;
	if (lvl < 0 && lvl >= INT_MIN)
		lvl = 0;
	else if(lvl > 2000000 ) 
	{
		msg = ft_strjoin(" shell level (", ft_itoa(lvl));
		tmp = ft_strdup(msg);
		free(msg);
		msg = ft_strjoin(tmp, ") too high, resetting to 1");
		free(tmp);
		print_errors(shell, msg, "warning");
		free(msg);
		lvl = 1;
	}
	shlvl = ft_itoa(lvl);
	tmp = ft_strjoin("SHLVL=", shlvl); 
	ft_export(shell, tmp);
	free(tmp);
	free(shlvl);
}
