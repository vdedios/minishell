/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2021/02/09 23:46:31 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*last_arg(char *arg)
{
	char *buff;
	if ((buff = ft_strchr(arg, '=')))
		*buff = '\0';
	return (ft_strjoin("_=", arg));
}

static char 	*update_last_arg(char **args)
{
	int len;

	len = 0;
	while (args[len])
		len++;
	return (last_arg(args[len - 1]));
}

static	char	*append_pwd(char *value)
{
	char	cwd[1024];
	char	*aux;

	aux = value;
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (value[0] == ':')
			return (ft_strjoin(cwd, value));
		if (value[ft_strlen(value) - 1] == ':')
			return (ft_strjoin(value, cwd));
		while (*aux)
		{
			if (!(aux = ft_strchr(aux, ':')))
				break;
			if (*(aux + 1) == ':')
				return (ft_strjoin(value, cwd));
			aux++;
		}
	}
	return (ft_strdup(value));
}

char 			*get_path(t_shell *shell, int *binary)
{
	char *value;
	char *tmp;
	char *path;
	char **paths;

	value = get_env(shell, "PATH");
	if (!value || ft_strlen(value) == 0)
		path = search_binary_in_pwd(shell);
	else
	{
		tmp = append_pwd(value);
		paths = ft_split(tmp, ':');
		path = search_binary(shell, paths, binary);
		//clean_matrix(paths);
		free(paths);
	}
	
	return (path);
}

int 			run_command(t_shell *shell)
{
	pid_t pid;
	int binary;
	char *path;

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
	waitpid(pid, &shell->stat_loc, 0);
	if (WIFEXITED(shell->stat_loc))
		shell->stat_loc = WEXITSTATUS(shell->stat_loc);
	if (shell->stat_loc == -1)
		ft_putstr_fd("\n", 1);
	ft_export(shell, update_last_arg(shell->args));
	free(path);
	return (1);
}

static char 	*to_lower(char *input)
{
	size_t it;
	char *output;

	output = calloc(1, ft_strlen(input));
	it = -1;
	while (input[++it])
	{
		output[it] = ft_tolower(input[it]);
	}
	output[it] = '\0';
	return (output);
}

int 			check_builtin(t_shell *shell)
{
	int ret;

	ret = 0;
	//to_lower(shell->args[0]);
	if (ft_strcmp(shell->args[0], "exit"))
		ft_exit(shell);
	else if (ft_strcmp(shell->args[0], "echo"))
		ret = ft_echo(shell->args + 1);
	else if (ft_strcmp(shell->args[0], "cd"))
		ret = ft_cd(shell);
	else if (ft_strcmp(*shell->args, "pwd"))
		ret = ft_pwd();
	else if (ft_strcmp(*shell->args, "export"))
	{
		delete_environment(shell, "_", shell->env);
		ret = ft_export(shell, NULL);
	}
	else if (ft_strcmp(*shell->args, "unset"))
		ret = ft_unset(shell);
	else if (ft_strcmp(to_lower(shell->args[0]), "env"))
	{
		ft_export(shell, ft_strjoin("_=", get_path(shell, NULL)));
		return(ft_env(shell, shell->env));
	}
	ft_export(shell, update_last_arg(shell->args));
	return (ret);
}

static void 	handle_commands(t_shell *shell)
{
	int		fd;
	char	*tmp;

	fd = -2;
	if (*(shell->commands + 1))
		find_pipes(shell);
	else if (shell->commands[0])
	{
		tmp = expansion(shell, shell->commands[0]);
		free(shell->commands[0]);
		shell->commands[0] = tmp;
		shell->args = get_args(shell->commands[0]);
		shell->binary = ft_strdup(shell->args[0]);
		fd = find_redirections(shell);
		if (fd != -1)
			if (shell->args[0] && !(check_builtin(shell)))
				run_command(shell);
		close(fd);
	}
}

static char		*get_var_key(char *line, int it)
{
	int		i;
	int		k;
	char	*key;

	i = it;
	k = 0;
	while (i >= 0 && line[i] != '{')
		i--;
	if (!(key = malloc((it - i) * sizeof(char))))
		return (NULL);
	i++;
	while (i < it)
		key[k++] = line[i++];
	key[k] = '\0';
	return (key);
}

static short	contain_spaces(char *value)
{
	while (*value)
	{
		if (*value == ' ')
			return (1);
		value++;
	}
	return (0);
}

static char 	*post_to_token(t_shell *shell, char *line, int it, char token)
{
	char	*key;
	char	*value;

	if (token == '>')
		while (line[it++])
			if (line[it] == '}' && line[it - 1] != ' ')
			{
				key = get_var_key(line, it);
				value = expand_var(key, shell);
				if (contain_spaces(value))
					return (ft_strjoin("$", key));
			}
	return (NULL);
}

static short 	prior_to_token(char *line, int it, char token)
{
	int aux_it;

	aux_it = it;
	while (aux_it > 0 && line[aux_it] == ' ')
		aux_it--;
	if (token == '>' || token == '<')
		return (aux_it > 0 && aux_it != it &&
				(line[aux_it] == '>' ||
				line[aux_it] == '<'));
	else 
		return (aux_it < 1 ||
				line[aux_it] == ';' ||
				line[aux_it] == '>' ||
				line[aux_it] == '<' ||
				line[aux_it] == '|');
	return (0);
}

static short	nothing_after_pipe(char *line, int it)
{
	if ((it - 2) >= 0 && *(line - 2) == '\\')
		return (0);
	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (1);
	return (0);
}

static void 	validator(t_shell *shell, char *line, char separator, int it)
{
	char	*key;

	if (prior_to_token(line, it - 1, line[it]))
	{
		if (separator == ';')
			print_errors(shell, "syntax error near unexpected token `;'", NULL);
		else if (separator == '|')
			print_errors(shell, "syntax error near unexpected token `|'", NULL);
		else if (separator == '>' && line[it + 1] == '>')
			print_errors(shell, "syntax error near unexpected token `>>'", NULL);
		else if (separator == '>')
			print_errors(shell, "syntax error near unexpected token `>'", NULL);
		else if (separator == '<' && line[it + 1] == '<')
			print_errors(shell, "syntax error near unexpected token `<<'", NULL);
		else if (separator == '<')
			print_errors(shell, "syntax error near unexpected token `<'", NULL);
		exit(2);
		// Arreglarlo para que no salga de la ejecucion principal
		//shell->stat_loc = 2;
	}
	else if (separator == '|' && nothing_after_pipe(&line[it + 1], it))
	{
		print_errors(shell, "line 1: syntax error: unexpected end of file", NULL);
		exit(2);
	}
	else if ((key = post_to_token(shell, line, it, line[it])))
	{
		print_errors(shell, ft_strjoin(key,": ambiguous redirect" ), NULL);
		exit(1);
	}
}

static void 	validate_input(t_shell *shell, char *line)
{
	int it;

	it = -1;
	while (line[++it])
		if (line[it] == '|' ||
			line[it] == '<' ||
			line[it] == '>' ||
			line[it] == ';')
			validator(shell, line, line[it], it);
		if (line[it + 1] == '<' || line[it + 1] == '>')
			it++;
}

static char		*inject_spaces(char *line)
{
	size_t	it;
	size_t	cont;
	//size_t 	len;
	char	*output;

	it = -1;
	cont = 0;
	while (line[++it])
	{
		if (line[it] == '>' && line[it - 1] != ' ' && line[it - 1] != '>')
			cont++;
		if (line[it] == '>' && line[it + 1] != ' ')
			cont++;
		if (line[it] == '<' && line[it - 1] != ' ' && line[it - 1] != '<')
			cont++;
		if (line[it] == '<' && line[it + 1] != ' ')
			cont++;
	}
	output = calloc(1, ft_strlen(line) + cont + 1);
	while (*line == ' ')
	{
		line++;
	}
	it = -1;
	while (line[++it])
	{
		//printf("U: %zu-%c\n", it, line[it]);
		if (line[it] == '>')
		{
			ft_strlcat(output, line, ft_strlen(output) + it + 1);
			if (line[it - 1] != ' ' && line[it - 1] != '>')
			{
				ft_strlcat(output, " ", ft_strlen(output) + 2);
			}
			ft_strlcat(output, line + it, ft_strlen(output) + 2);
			if (line[it + 1] != ' ' && line[it + 1] != '>')
			{
				ft_strlcat(output, " ", ft_strlen(output) + 2);
			}
			line = line + it + 1;
			it = -1;
		}
		if (line[it] == '<')
		{
			ft_strlcat(output, line, ft_strlen(output) + it + 1);
			if (line[it - 1] != ' ' && line[it - 1] != '<')
			{
				ft_strlcat(output, " ", ft_strlen(output) + 2);
			}
			ft_strlcat(output, line + it, ft_strlen(output) + 2);
			if (line[it + 1] != ' ' && line[it + 1] != '<')
			{
				ft_strlcat(output, " ", ft_strlen(output) + 2);
			}
			line = line + it + 1;
			it = -1;
		}
	}
	ft_strlcat(output, line, line - output);
	//printf("S: %s", output);
	return (output);
}

static void 	minishell(char *line, t_shell *shell)
{
	size_t 	it;
	size_t	jt;
	char	*tmp;

	it = 0;
	jt = 0;
	tmp = inject_spaces(line);
	free(line);
	line = tmp;
	validate_input(shell, line);
	shell->instructions = ft_split_non_escaped(line, ';');	
	free(line);
	while (shell->instructions[it])
	{
		shell->stat_loc = 0;
		while (is_space(shell->instructions[it][jt]))
			jt++;
		shell->commands = ft_split_non_escaped(&shell->instructions[it][jt], '|');
		free(shell->instructions[it]);
		handle_commands(shell);
		shell->previous_stat = shell->stat_loc;
		it++;
	}
	//clean_commands(shell);
}

static void 	read_input(char *line, t_shell *shell)
{
	char *tmp;

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
		tmp = parse_input(line);
		free(line);
		line = tmp;
		minishell(line, shell);
	}
}

int 			main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*line;
	char	*tmp;
	char	curr_pwd[1024];

	shell.stat_loc = 0;
	line = NULL;
	shell.instructions = NULL;
	shell.env = ft_strdup_matrix(envp);
	getcwd(curr_pwd, 1024);
	ft_export(&shell, ft_strjoin("PWD=", curr_pwd));
	handle_shlvl(&shell);
	ft_export(&shell, ft_strdup("_=/bin/bash"));
	if (argc == 3 && ft_strcmp(argv[1], "-c"))
	{
		line = ft_strdup(argv[2]);
		tmp = parse_input(line);
		free(line);
		line = tmp;
		minishell(line, &shell);
		//free(line);
	}
	else
		read_input(line, &shell);
	return (shell.stat_loc);
}
