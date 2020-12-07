/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2020/12/07 14:38:42 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_command(t_shell *shell, char exited)
{
	char	*value;
	char	*path;
	char	**paths;
	pid_t	pid;

	value = get_env(shell->env, "PATH");
	paths = ft_split(value, ':');
	path = search_binary(shell, paths, exited);
	pid = fork();
	if (pid == 0)
	{
		if (path)
			path = absolute_bin_path(path, shell->args[0]);
		else
		{
			path = ft_strdup(shell->binary);
			check_permissions(shell, path, exited);
		}
		execve(path, shell->args, shell->env);
		shell->stat_loc = 127;
		//print_errors(shell, " command not found", shell->args[0], exited);
	}

	signal(SIGINT, signal_handler_waiting);
	wait(&shell->stat_loc);
	shell->stat_loc = WEXITSTATUS(shell->stat_loc);
	if (shell->stat_loc == -1)
		ft_putstr_fd("\n", 1);
	clean_matrix(paths);
	free(paths);
	return (1);
}

int		check_builtin(t_shell *shell)
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

static void		handle_commands(t_shell *shell, char exited)
{
	int		fd_out;
	int		fd_in;
	int		fd;

	fd = -2;
	fd_out = dup(1);
	fd_in = dup(0);
	if (*(shell->commands + 1))
		find_pipes(shell);
	else
	{
		shell->args = get_args(*shell->commands);
		expansion(shell);
		shell->binary = ft_strdup(shell->args[0]);
		fd = find_redirections(shell, exited);
		if (fd != -1)
			if (shell->args[0] && !(check_builtin(shell)))
				run_command(shell, exited);
		close(fd);
		dup2(fd_out, 1);
		dup2(fd_in, 0);
	}
}

static void		minishell(char *line, t_shell *shell)
{
	size_t	it;
	char	exited;

	it = 0;
	exited = 0;
	shell->instructions = ft_split(line, ';');
	if (!(shell->instructions[0]))
	{
		shell->stat_loc = 2;
		print_errors(shell, "syntax error near unexpected token `;'", NULL, exited);
	}
	while (shell->instructions[it])
	{
		shell->stat_loc = 0;
		shell->instructions[it] = ft_strtrim(shell->instructions[it], " ");
		shell->commands = ft_split(shell->instructions[it], '|');
		if (ft_strchr(shell->instructions[it], '|'))
		{
			if (!(shell->commands[0]) || (shell->commands[0] && (!shell->commands[1])))
			{
				shell->stat_loc = 2;
				print_errors(shell, "syntax error near unexpected token `|'", NULL, exited);
			}
		}
		if (shell->instructions[it + 1])
			exited = 0;
		handle_commands(shell, exited);
		shell->previous_stat = shell->stat_loc;
		it++;
	}
	//clean_commands(shell);
}

static void		read_input(char *line, t_shell *shell)
{
	signal(SIGQUIT, signal_handler_running);
	signal(SIGTERM, signal_handler_running);
	while (1)
	{
		signal(SIGINT, signal_handler_running);
		ft_putstr_fd("$:\\>", 1);
		if (get_next_line(&line) == 0)
		{
			ft_putendl_fd("exit", 1);
			clean_shell(shell);
			free(line);
			exit(0);
		}
		minishell(line, shell);
		free(line);
	}
}

int				main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	shell.stat_loc = 0;
	line = NULL;
	shell.env = ft_strdup_matrix(envp);
	shell.instructions = NULL;
	if (argc == 3 && ft_strcmp(argv[1], "-c"))
	{
		line = ft_strdup(argv[2]);
		minishell(line, &shell);
		free(line);
	}
	else
		read_input(line, &shell);
	return (shell.stat_loc);
}
