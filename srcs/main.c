/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2020/10/10 22:36:27 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		run_command(t_shell *shell)
{
	char	*value;
	char	*path;
	char	**paths;
	
	value = get_env(shell->env, "PATH");
	paths = ft_split(value, ':');
	path = search_binary(shell->args[0], paths);
	if (path)
		path = absolute_bin_path(path, shell->args[0]);
	else
		path = ft_strdup(shell->args[0]);
	if (fork() == 0)
	{
		execve(path, shell->args, shell->env);
		print_errors(" command not found ", shell->args[0]);
	}
	signal(SIGINT, signal_handler_waiting);
	wait(&shell->stat_loc);
	if (shell->stat_loc)
		ft_putstr_fd("\n", 1);
	free(path);
	clean_matrix(paths);
	free(paths);
	return (1);
}

static int		check_builtin(t_shell *shell)
{
	if (ft_strcmp(*shell->args, "exit"))
		ft_exit(shell);
	else if (ft_strcmp(*shell->args, "echo"))
		return (ft_echo(shell->args + 1));
	else if (ft_strcmp(*shell->args, "cd"))
		return (ft_cd(shell));
	else if (ft_strcmp(*shell->args, "pwd"))
		return (ft_pwd());
	else if (ft_strcmp(*shell->args, "export"))
		return (ft_export(shell));
	else if (ft_strcmp(*shell->args, "unset"))
		return (ft_unset(shell->args[1], shell->env));
	else if (ft_strcmp(*shell->args, "env"))
		return (ft_env(shell->args + 1, shell->env));
	return (0);
}

static void		run_commands(t_shell *shell)
{
	size_t	it;
	int		saved_stdout;
	int		saved_stdin;
	int		fd;

	saved_stdout = dup(1);
	saved_stdin = dup(0);
	it = 0;
	while (shell->commands[it])
	{
		shell->args = get_args(shell->commands[it]);
		fd = find_redirections(shell);
		expansion(shell);
		if (!check_builtin(shell))
			run_command(shell);
		dup2(saved_stdout, 1);
		dup2(saved_stdin, 0);
		close(fd);
		it++;
	}
}

static void		minishell(t_shell *shell)
{
	char	*line;

	signal(SIGQUIT, signal_handler_running);
	while (1)
	{
		line = NULL;
		signal(SIGINT, signal_handler_running);
		ft_putstr_fd("$:\\>", 1);
		if (get_next_line(&line) == 0)
		{
			ft_putendl_fd("exit", 1);
			clean_shell(shell);
			free(line);
			exit(0);
		}
		shell->commands = ft_split(line, ';');
		free(line);
		run_commands(shell);
		clean_commands(shell);
	}
}

int				main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = ft_strdup_matrix(envp);
	shell.commands = NULL;
	shell.args = NULL;
	minishell(&shell);
	return (0);
}
