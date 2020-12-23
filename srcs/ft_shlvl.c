/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:36:17 by migferna          #+#    #+#             */
/*   Updated: 2020/12/23 20:04:21 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_shlvl(t_shell *shell)
{
	char					*shlvl;
	int						lvl;
	char					*msg;

	shlvl = get_env(shell, "SHLVL=");
	if (!shlvl)
		shlvl = "0";
	lvl = (int)ft_atoi(shlvl) + 1;
	//if (lvl == 0)
	//	printf("Valor: %d", lvl);
	//	lvl = 1;
	if (lvl < 0 && lvl >= -2147483648)
		lvl = 0;
	else if(lvl > 2000000 ) 
	{
		msg = ft_strjoin(" shell level (", ft_itoa(lvl));
		msg = ft_strjoin(msg, ") too high, resetting to 1");
		print_errors(shell, msg, "warning", 0);
		lvl = 1;
	}
	//else if (lvl >= 2147483648 || lvl < 0)
	//	lvl = 0;
	/*else if (lvl > 2147483647 && lvl < 4294967295)
		lvl = 0;
	else if (lvl >= 4294967295)
		lvl = 1;
	else if (lvl == 0) lvl = 0;*/
	shlvl = ft_itoa(lvl);
	ft_export(shell, ft_strjoin("SHLVL=", shlvl));
}
