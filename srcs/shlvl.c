/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:36:17 by migferna          #+#    #+#             */
/*   Updated: 2021/02/18 19:09:48 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		shlvl_error(t_shell *shell, int lvl)
{
	char *tmp;
	char *msg;

	tmp = ft_itoa(lvl);
	msg = ft_strjoin(" shell level (", tmp);
	free(tmp);
	tmp = ft_strdup(msg);
	free(msg);
	msg = ft_strjoin(tmp, ") too high, resetting to 1");
	free(tmp);
	print_errors(shell, msg, "warning");
	free(msg);
}

void			handle_shlvl(t_shell *shell)
{
	char					*shlvl;
	int						lvl;
	char					*tmp;

	shlvl = get_env(shell, "SHLVL=");
	if (!shlvl)
	{
		free(shlvl);
		shlvl = "0";
	}
	lvl = (int)ft_atoi(shlvl) + 1;
	free(shlvl);
	if (lvl < 0 && lvl >= INT_MIN)
		lvl = 0;
	else if (lvl > 2000000)
	{
		shlvl_error(shell, lvl);
		lvl = 1;
	}
	shlvl = ft_itoa(lvl);
	tmp = ft_strjoin("SHLVL=", shlvl);
	ft_export(shell, tmp);
	free(tmp);
	free(shlvl);
}
