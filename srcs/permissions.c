/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:16 by migferna          #+#    #+#             */
/*   Updated: 2021/02/21 00:15:39 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_err_message(t_shell *shell, char *err, int code, char *arg)
{
	shell->stat_loc = code;
	print_errors(shell, err, arg);
	return (0);
}

int			check_permissions(t_shell *shell, char *path)
{
	struct stat s;

	if (stat(path, &s) != -1)
	{
		if (s.st_mode & S_IFDIR)
			return (set_err_message(shell, " is a directory", 126
					, shell->binary));
		if (shell->is_binary == 1 && (!(s.st_mode & S_IXUSR)))
			return (set_err_message(shell, " Permission denied", 126, path));
		else if (shell->is_binary == 0 &&
				(!(s.st_mode & S_IXUSR) || !(s.st_mode & S_IRUSR)))
			return (set_err_message(shell, " Permission denied", 126, path));
		return (1);
	}
	else
		return (set_err_message(shell, " command not found", 127
					, shell->binary));
}
