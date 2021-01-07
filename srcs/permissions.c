/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 12:53:16 by migferna          #+#    #+#             */
/*   Updated: 2021/01/05 19:01:39 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_permissions(t_shell *shell, char *path, char exited)
{
	struct stat s;

	if (stat(path, &s) != -1)
	{
		//printf("Path: %d\n", *bin);
		if (s.st_mode & S_IFDIR)
		{
			shell->stat_loc = 126;
			print_errors(shell, " is a directory", shell->binary, exited);
			exit(shell->stat_loc);
		}
		if ( !(s.st_mode & S_IXUSR))
		//if ((s.st_mode & S_IRWXU) == S_IXUSR)
		//if (!(s.st_mode & S_IXUSR) || ((s.st_mode & S_IXUSR) && !(s.st_mode & S_IRUSR)))
		//if (!(s.st_mode & S_IRUSR) || (s.st_mode & S_IRUSR && (!(s.st_mode & S_IXUSR))))
		{
			shell->stat_loc = 126;
			print_errors(shell, " Permission denied", path, exited);
			exit(shell->stat_loc);
		}
		
	}
	else
	{
		shell->stat_loc = 127;
		print_errors(shell, " command not found", shell->binary, exited);
		exit(shell->stat_loc);
	}
}
