/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:09:49 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 22:34:09 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(t_shell *shell)
{
	char		cwd[1024];
	char		*tmp;

	tmp = get_env(shell, "PWD");
	if (is_symbolic_link(tmp))
		ft_putendl_fd(tmp, 1);
	else if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
	free(tmp);
	return (1);
}
