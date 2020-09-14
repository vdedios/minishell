/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2020/09/14 11:23:02 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		run_command(t_shell *shell)
{
	char	*path;
	char	*value;
	char	**paths;
	char	*bin;

	value = get_env(shell->env, "PATH");
	paths = ft_split(value, ':');
	path = search_binary(shell->args[0], paths);
	if (path)
	{
		bin = ft_strjoin("/", shell->args[0]);
		path = ft_strjoin(path, bin);
	}
	else
		path = shell->args[0];
	if (fork() == 0)
	{
		execve(path, shell->args, shell->env);
		ft_putstr_fd("minishell: command not found ", 1);
		ft_putstr_fd(bin, 1);
		ft_putstr_fd("\n", 1);
		exit(0);
	}
	wait(&shell->stat_loc);
	return (1);
}

static int		check_builtin(t_shell *shell)
{
	if (!ft_strncmp(*shell->args, "echo", ft_strlen("echo")))
		return (ft_echo(shell->args + 1));
	else if (!ft_strncmp(*shell->args, "cd", ft_strlen("cd")))
		return (ft_cd(shell->args + 1, shell->env));
	else if (!ft_strncmp(*shell->args, "pwd", ft_strlen("pwd")))
		return (ft_pwd());
	else if (!ft_strncmp(*shell->args, "export", ft_strlen("export")))
		return (ft_export(shell->args + 1, shell));
	else if (!ft_strncmp(*shell->args, "unset", ft_strlen("unset")))
		return (ft_unset(shell->args[1], shell->env));
	else if (!ft_strncmp(*shell->args, "env", ft_strlen("env")))
		return (ft_env(shell->args + 1, shell->env));
	else if (!ft_strncmp(*shell->args, "exit", ft_strlen("exit")))
		return (ft_exit(shell->args + 1));
	return (0);
}

static void		run_commands(t_shell *shell)
{
	size_t	it;

	it = 0;
	while (shell->commands[it])
	{
		shell->args = get_args(shell->commands[it]);
		expand_var(shell);
		if (!check_builtin(shell))
			run_command(shell);
		it++;
	}
}

static void		minishell(t_shell *shell)
{
	char	*line;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		ft_putstr_fd("$:\\>", 1);
		if (get_next_line(&line) == 0)
		{
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		shell->commands = ft_split(line, ';');
		free(line);
		run_commands(shell);
	}
}

int				main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = ft_calloc(sizeof(t_shell), sizeof(shell));
	shell->env = envp;
	minishell(shell);
	free(shell);
	return (0);
}
