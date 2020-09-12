/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2020/09/12 11:50:38 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		run_command(char **args, char **env)
{
	char	*path;
	char	*value;
	char	**paths;
	char	*bin;

	value = get_env(env, "PATH");
	paths = ft_split(value, ':');
	path = search_binary(args[0], paths);
	bin = ft_strjoin("/", args[0]);
	path = ft_strjoin(path, bin);
	if (fork() == 0)
		execve(path, args, env);
	wait(NULL);
	return (1);
}

static int		check_builtin(char **args, char **env)
{
	if (!ft_strncmp(*args, "echo", ft_strlen("echo")))
		return (ft_echo(args + 1));
	else if (!ft_strncmp(*args, "cd", ft_strlen("cd")))
		return (ft_cd(args + 1, env));
	else if (!ft_strncmp(*args, "pwd", ft_strlen("pwd")))
		return (ft_pwd());
	else if (!ft_strncmp(*args, "export", ft_strlen("export")))
		return (0);
	else if (!ft_strncmp(*args, "unset", ft_strlen("unset")))
		return (ft_unset(args[1], env));
	else if (!ft_strncmp(*args, "env", ft_strlen("env")))
		return (ft_env(env));
	else if (!ft_strncmp(*args, "exit", ft_strlen("exit")))
		return (0);
	else
		return (run_command(args, env));
}

static int		run_commands(char **commands, char **env)
{
	char	**args;
	int		status;
	size_t	it;

	it = 0;
	status = 1;
	while (commands[it])
	{
		args = get_args(commands[it]);
		status = check_builtin(args, env);
		it++;
	}
	return (status);
}

static void		minishell(char **env)
{
	int		status;
	char	*line;
	char	**commands;

	status = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (status)
	{
		ft_putstr_fd("minishell:\\>", 1);
		if (get_next_line(0, &line) == 0)
		{
			ft_putendl_fd("exit\n", 1);
			exit(0);
		}
		commands = ft_split(line, ';');
		free(line);
		status = run_commands(commands, env);
	}
}

int				main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
