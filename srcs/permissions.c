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

void	check_permissions(t_shell *shell, char *path, int *binary)
{
	struct stat s;

	if (stat(path, &s) != -1)
	{
		//printf("Path: %s\n", path);
		if (s.st_mode & S_IFDIR)
		{
			shell->stat_loc = 126;
			print_errors(shell, " is a directory", shell->binary);
			exit(shell->stat_loc);
		}

		if (*binary == 1)
		{
			if (!(s.st_mode & S_IXUSR))
			{
				shell->stat_loc = 126;
				print_errors(shell, " Permission denied", path);
				exit(shell->stat_loc);
			}
		}
		else if (*binary == 0)
		{
			if (!(s.st_mode & S_IXUSR) || !(s.st_mode & S_IRUSR))
			{
				//printf("Usuario");
				shell->stat_loc = 126;
				print_errors(shell, " Permission denied", path);
				exit(shell->stat_loc);
			}
		}
		
	}
	else
	{
		shell->stat_loc = 127;
		print_errors(shell, " command not found", shell->binary);
		exit(shell->stat_loc);
	}
}
