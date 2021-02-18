/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:20:41 by migferna          #+#    #+#             */
/*   Updated: 2021/02/17 20:07:47 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		get_args_and_binary(t_shell *shell, int it)
{
	char	*tmp;

	tmp = expansion(shell, shell->commands[it]);
	free(shell->commands[it]);
	shell->args = get_args(tmp);
	free(tmp);
	shell->binary = ft_strdup(shell->args[0]);

}

static void		exec_arg(t_shell *shell)
{
	int	binary;
	char	*path;

	binary = 0;
	if (!check_builtin(shell))
	{
		path = get_path(shell, &binary);
		check_permissions(shell, path, &binary);
		execve(path, shell->args, shell->env);
	}
}


void	find_pipes(t_shell *shell)
{
	pid_t	pid;
	pid_t	aux_pid;
	int		p[2];
	int		it;

	it = 0;
	while (shell->commands[it])
	{
		get_args_and_binary(shell, it);
		pipe(p);
		if ((pid = fork()) == 0)
		{
			close(p[0]);
			if (shell->commands[it + 1])
				dup2(p[1], 1);
			find_redirections(shell);
			exec_arg(shell);
			close(p[1]);
			exit(shell->stat_loc);
		}
		close(p[1]);
		dup2(p[0], 0);
		it++;
		if (shell->commands[it])
			waitpid(pid, &shell->stat_loc, WNOHANG);
		shell->stat_loc = WEXITSTATUS(shell->stat_loc);
		close(p[0]);

		clean_matrix(shell->args);
		free(shell->args);
		free(shell->binary);
	}
	while ( (aux_pid = wait(&shell->stat_loc)) > 0)
	{
		if (aux_pid < pid)
			shell->stat_loc = WEXITSTATUS(shell->stat_loc);
	}
	shell->stat_loc = WEXITSTATUS(shell->stat_loc);
}
