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

static void	set_err_message(t_shell *shell, char *err, int code, char *arg)
{
	shell->stat_loc = code;
	print_errors(shell, err, arg);
}

int			check_permissions(t_shell *shell, char *path, int *binary)
{
	struct stat s;

	if (stat(path, &s) != -1)
	{
		if (s.st_mode & S_IFDIR)
		{
			set_err_message(shell, " is a directory", 126, shell->binary);
			return (0);
		}
		if (*binary == 1 && (!(s.st_mode & S_IXUSR)))
		{
			set_err_message(shell, " Permission denied", 126, path);
			return (0);
		}
		else if (*binary == 0 &&
				(!(s.st_mode & S_IXUSR) || !(s.st_mode & S_IRUSR)))
		{
			set_err_message(shell, " Permission denied", 126, path);
			return (0);
		}
		return (1);
	}
	else
	{
		set_err_message(shell, " command not found", 127, shell->binary);
		return (0);
	}
}
