/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:16 by migferna          #+#    #+#             */
/*   Updated: 2021/02/15 22:57:20 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_err_message(t_shell *shell, char *err, int code, char *arg)
{
	shell->stat_loc = code;
	print_errors(shell, err, arg);
	exit(shell->stat_loc);
}

void	check_permissions(t_shell *shell, char *path, int *binary)
{
	struct stat s;

	if (stat(path, &s) != -1)
	{
		if (s.st_mode & S_IFDIR)
			set_err_message(shell, " is a directory", 126, shell->binary);
		if (*binary == 1 && (!(s.st_mode & S_IXUSR)))
			set_err_message(shell, " Permission denied", 126, path);
		else if (*binary == 0 &&
				(!(s.st_mode & S_IXUSR) || !(s.st_mode & S_IRUSR)))
				set_err_message(shell, " Permission denied", 126, path);
	}
	else
		set_err_message(shell, " command not found", 127, shell->binary);
}
