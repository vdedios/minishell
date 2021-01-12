/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:20:41 by migferna          #+#    #+#             */
/*   Updated: 2021/01/12 19:20:35 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_pipes(t_shell *shell)
{
	pid_t	pid;
	int		p[2];
	int		fd_in;
	int		it;
	int		fd;
	char	*path;
	int		binary;

	fd_in = 0;
	it = 0;
	binary = 0;
	while (shell->commands[it])
	{
		shell->args = get_args(shell->commands[it]);
		shell->binary = ft_strdup(shell->args[0]);
		pipe(p);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			close(p[0]);
			dup2(fd_in, 0);
			if (shell->commands[it + 1])
				dup2(p[1], 1);
			close(p[1]);
			fd = find_redirections(shell);
			if (!check_builtin(shell))
			{
				path = get_path(shell, &binary);
				check_permissions(shell, path, &binary);
				execve(path, shell->args, shell->env);
			}
			close(fd);
			exit(shell->stat_loc);
		}
		else
		{
			waitpid(pid, &shell->stat_loc, WNOHANG);
			close(p[1]);
			fd_in = p[0];
			it++;
		}
	}
}
