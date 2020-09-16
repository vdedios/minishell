/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2020/09/16 20:03:23 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		run_command(t_shell *shell)
{
	char	*path;
	char	*value;
	char	**paths;
	char	*bin;
	pid_t	pid;

	bin = shell->args[0];
	value = get_env(shell->env, "PATH");
	paths = ft_split(value, ':');
	path = search_binary(bin, paths);
	if (path)
	{
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, bin);
	}
	else
		path = bin;
	pid = fork();
	signal(SIGINT, signal_handler_children);
	signal(SIGQUIT, signal_handlerd_children);
	if (pid == 0)
	{
		execve(path, shell->args, shell->env);
		print_errors(" command not found ", bin);
	}
	wait(&shell->stat_loc);
	//liberar memoria
	//free(bin)
	//free(path)
	//free(paths)
	//free(value)
	return (1);
}

static int		check_builtin(t_shell *shell)
{
	if (ft_strcmp(*shell->args, "exit"))
		ft_exit(shell->args + 1);
	else if (ft_strcmp(*shell->args, "echo"))
		return (ft_echo(shell->args + 1));
	else if (ft_strcmp(*shell->args, "cd"))
		return (ft_cd(shell->args + 1, shell->env));
	else if (ft_strcmp(*shell->args, "pwd"))
		return (ft_pwd());
	else if (ft_strcmp(*shell->args, "export"))
		//Cambiar y pasar solo shell
		return (ft_export(shell->args + 1, shell));
	else if (ft_strcmp(*shell->args, "unset"))
		return (ft_unset(shell->args[1], shell->env));
	else if (ft_strcmp(*shell->args, "env"))
		return (ft_env(shell->args + 1, shell->env));
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

	//Revisar como funciona wait con callbacks
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, signal_handlerd_parent);
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
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = envp;
	minishell(&shell);
	return (0);
}
