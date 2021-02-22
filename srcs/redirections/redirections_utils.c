/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:01:20 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 15:27:40 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redirections_append(t_shell *shell, size_t it)
{
	int fd;

	fd = -1;
	if (!(shell->args[it + 1]))
	{
		shell->stat_loc = 2;
		print_errors(shell,
				"syntax error near unexpected token `newline'", NULL);
	}
	else
	{
		if ((fd = open(shell->args[it + 1],
						O_CREAT | O_APPEND | O_WRONLY, 0644)) == -1)
		{
			shell->stat_loc = 1;
			print_errors(shell,
					" No such file or directory", shell->args[it + 1]);
		}
		else
			dup2(fd, 1);
		delete_environment(shell, shell->args[it], shell->args);
	}
	delete_environment(shell, shell->args[it], shell->args);
	return (fd);
}

int		redirections_output(t_shell *shell, size_t it)
{
	int fd;

	fd = -1;
	if (!(shell->args[it + 1]))
	{
		shell->stat_loc = 2;
		print_errors(shell,
				"syntax error near unexpected token `newline'", NULL);
	}
	else
	{
		if ((fd = open(shell->args[it + 1],
						O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		{
			shell->stat_loc = 1;
			print_errors(shell,
					" No such file or directory", shell->args[it + 1]);
		}
		else
			dup2(fd, 1);
		delete_environment(shell, shell->args[it], shell->args);
	}
	delete_environment(shell, shell->args[it], shell->args);
	return (fd);
}

short	redirection_exists(t_shell *shell, size_t it)
{
	struct stat	s;
	int			fd;

	fd = -1;
	if ((fd = open(shell->args[it + 1], O_RDONLY, 0644)) == -1)
	{
		if (stat(shell->args[it + 1], &s) != -1)
		{
			if (!(s.st_mode & S_IRUSR) ||
					(s.st_mode & S_IRUSR && (!(s.st_mode & S_IXUSR))))
			{
				shell->stat_loc = 1;
				print_errors(shell, " Permission denied", shell->args[it + 1]);
			}
		}
		else
		{
			shell->stat_loc = 1;
			print_errors(shell,
					" No such file or directory", shell->args[it + 1]);
		}
	}
	return (fd);
}
