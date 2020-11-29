/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:20:41 by migferna          #+#    #+#             */
/*   Updated: 2020/11/29 15:09:15 by migferna         ###   ########.fr       */
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

	fd_in = 0;
	it = 0;
	while (shell->commands[it])
	{
		shell->args = get_args(shell->commands[it]);
		pipe(p);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2(fd_in, 0);
			if (shell->commands[it + 1])
				dup2(p[1], 1);
			close(p[0]);
			fd = find_redirections(shell);
			if (!check_builtin(shell))
				run_command(shell);
			close(fd);
			exit(shell->stat_loc);
		}
		else
		{
			wait(&shell->stat_loc);
			close(p[1]);
			fd_in = p[0];
			it++;
		}
	}
}
