/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2021/01/12 18:58:04 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*update_last_arg(char **args)
{
	int		len;

	len = 0;
	while (args[len])
		len++;
	if (len > 1)
		return (ft_strjoin("_=", args[len - 1]));
	return (ft_strdup("_="));
}

char	*get_path(t_shell *shell, int *binary)
{
	char	*value;
	char	*path;
	char	**paths;

	value = get_env(shell, "PATH");
	paths = ft_split(value, ':');
	path = search_binary(shell, paths, binary);
	//clean_matrix(paths);
	free(paths);
	return (path);
}

int		run_command(t_shell *shell)
{
	char	*path;
	pid_t	pid;
	int		binary;

	binary = 0;
	path = get_path(shell, &binary);
	pid = fork();
	if (pid == 0)
	{
		check_permissions(shell, path, &binary);
		execve(path, shell->args, shell->env);
		exit(shell->stat_loc);
	}
	signal(SIGINT, signal_handler_waiting);
	wait(&shell->stat_loc);
	shell->stat_loc = WEXITSTATUS(shell->stat_loc);
	if (shell->stat_loc == -1)
		ft_putstr_fd("\n", 1);
	ft_export(shell, update_last_arg(shell->args));
	//free(path);
	return (1);
}

int				check_builtin(t_shell *shell)
{
	int ret;

	ret = 0;
	if (ft_strcmp(*shell->args, "exit"))
		ft_exit(shell);
	else if (ft_strcmp(*shell->args, "echo"))
		ret = ft_echo(shell->args + 1);
	else if (ft_strcmp(*shell->args, "cd"))
		ret = ft_cd(shell);
	else if (ft_strcmp(*shell->args, "pwd"))
		ret = ft_pwd();
	else if (ft_strcmp(*shell->args, "export"))
		ret = ft_export(shell, NULL);
	else if (ft_strcmp(*shell->args, "unset"))
		ret = ft_unset(shell->args[1], shell->env);
	else if (ft_strcmp(*shell->args, "env"))
		ret = ft_env(shell, shell->env);
	ft_export(shell, update_last_arg(shell->args));
	return (ret);
}

static void		handle_commands(t_shell *shell)
{
	int		fd_out;
	int		fd_in;
	int		fd;

	fd = -2;
	fd_out = dup(1);
	fd_in = dup(0);
	if (*(shell->commands + 1))
		find_pipes(shell);
	else if (shell->commands[0])
	{
		shell->commands[0] = expansion(shell, shell->commands[0]);
		shell->args = get_args(*shell->commands);
		shell->binary = ft_strdup(shell->args[0]);
		fd = find_redirections(shell);
		if (fd != -1)
			if (shell->args[0] && !(check_builtin(shell)))
				run_command(shell);
		close(fd);
		dup2(fd_out, 1);
		dup2(fd_in, 0);
	}
}

static void 	validator(t_shell *shell, char *line, char separator)
{
    size_t  it;
    size_t  cont;
    cont = 0;
    it = -1;
    while (line[++it])
    {
        if (line[it] != ' ' && line[it] != separator)
            cont++;
        else if (line[it] == separator)
        {
            if (cont == 0)
            {
				if (separator == ';')
                	print_errors(shell, "syntax error near unexpected token `;'", NULL);
				else if (separator == '|')
                	print_errors(shell, "syntax error near unexpected token `|'", NULL);
                exit(2);
            }
            else
                cont = 0;
        }
    }
}

static void		minishell(char *line, t_shell *shell)
{
	size_t	it;

	it = 0;
	validator(shell, line, ';');
	shell->instructions = ft_split_non_escaped(line, ';');
	while (shell->instructions[it])
	{
		shell->stat_loc = 0;
		while (is_space(*shell->instructions[it]))
			shell->instructions[it]++;
		validator(shell, shell->instructions[it], '|');
		shell->commands = ft_split_non_escaped(shell->instructions[it], '|');
		handle_commands(shell);
		shell->previous_stat = shell->stat_loc;
		it++;
	}
	//clean_commands(shell);
}

static void		read_input(char *line, t_shell *shell)
{
	signal(SIGQUIT, signal_handler_running);
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
		line = parse_input(line);
		minishell(line, shell);
		free(line);
		line = NULL;
	}
}

int				main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	char	curr_pwd[1024];

	shell.stat_loc = 0;
	line = NULL;
	shell.env = ft_strdup_matrix(envp);
	getcwd(curr_pwd, 1024);
	ft_export(&shell, ft_strjoin("PWD=", curr_pwd));
	ft_export(&shell, ft_strdup("OLDPWD="));
	shell.instructions = NULL;
	handle_shlvl(&shell);
	if (argc == 3 && ft_strcmp(argv[1], "-c"))
	{
		line = ft_strdup(argv[2]);
		line = parse_input(line);
		minishell(line, &shell);
		free(line);
	}
	else
		read_input(line, &shell);
	//printf("%s\n", embrace_expansion("echo $PWD$PWD"));
	return (shell.stat_loc);
}
