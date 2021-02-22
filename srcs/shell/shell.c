/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 22:25:19 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		handle_commands(t_shell *shell)
{
	char	*tmp;

	if (*(shell->commands + 1))
		find_pipes(shell);
	else if (shell->commands[0])
	{
		tmp = expansion(shell, shell->commands[0]);
		shell->args = get_args(tmp);
		shell->binary = ft_strdup(shell->args[0]);
		if (find_redirections(shell) != -1)
			if (shell->args[0] && !(check_builtin(shell)))
				run_command(shell);
		clean_matrix(shell->args);
		free(shell->args);
		free(tmp);
		free(shell->commands[0]);
		free(shell->binary);
	}
}

char			*get_path(t_shell *shell)
{
	char *value;
	char *tmp;
	char *path;
	char **paths;

	value = get_env(shell, "PATH");
	if (!value || ft_strlen(value) == 0)
	{
		free(value);
		path = search_binary_in_pwd(shell);
	}
	else
	{
		tmp = append_pwd(value);
		paths = ft_split(tmp, ':');
		path = search_binary(shell, paths);
		free(value);
		free(tmp);
		clean_matrix(paths);
		free(paths);
	}
	return (path);
}

int				run_command(t_shell *shell)
{
	pid_t	pid;
	char	*path;
	char	*tmp;

	shell->is_binary = 0;
	path = get_path(shell);
	if (path)
	{
		if ((pid = fork()) == 0 && check_permissions(shell, path))
		{
			execve(path, shell->args, shell->env);
			exit(shell->stat_loc);
		}
		signal(SIGINT, signal_handler_waiting);
		waitpid(pid, &shell->stat_loc, 0);
		if (WIFEXITED(shell->stat_loc))
			shell->stat_loc = WEXITSTATUS(shell->stat_loc);
		if (shell->stat_loc == -1)
			ft_putstr_fd("\n", 1);
		tmp = update_last_arg(shell->args);
		ft_export(shell, tmp);
		free(tmp);
	}
	free(path);
	return (1);
}

int				check_builtin(t_shell *shell)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (ft_strcmp(shell->args[0], "exit"))
		ft_exit(shell);
	else if (ft_strcmp(shell->args[0], "echo"))
		ret = ft_echo(shell->args + 1);
	else if (ft_strcmp(shell->args[0], "cd"))
		ret = ft_cd(shell);
	else if (ft_strcmp(*shell->args, "pwd"))
		ret = ft_pwd(shell);
	else if (ft_strcmp(*shell->args, "export"))
		ret = exec_export(shell);
	else if (ft_strcmp(*shell->args, "unset"))
		ret = ft_unset(shell);
	else
		return (exec_env(shell));
	tmp = update_last_arg(shell->args);
	ft_export(shell, tmp);
	free(tmp);
	return (ret);
}

void			minishell(char *line, t_shell *shell)
{
	size_t	it;
	size_t	jt;

	it = 0;
	line = safe_allocate(line, inject_spaces);
	if (validate_input(shell, line))
	{
		shell->instructions = ft_split_non_escaped(line, ';');
		while (shell->instructions[it])
		{
			jt = 0;
			shell->stat_loc = 0;
			while (is_space(shell->instructions[it][jt]))
				jt++;
			shell->commands = ft_split_non_escaped(&shell->instructions[it][jt],
					'|');
			handle_commands(shell);
			shell->previous_stat = shell->stat_loc;
			free(shell->commands);
			it++;
		}
	}
	free(line);
}
