/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 16:15:45 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*last_arg(char *arg)
{
	char	*buff;

	if ((buff = ft_strchr(arg, '=')))
		*buff = '\0';
	return (ft_strjoin("_=", arg));
}

static char		*update_last_arg(char **args)
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
				break ;
			if (*(aux + 1) == ':')
				return (ft_strjoin(value, cwd));
			aux++;
		}
	}
	return (ft_strdup(value));
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

static char		*to_lower(char *input)
{
	size_t	it;
	char	*output;
	char	*tmp;

	tmp = ft_strdup(input);
	output = calloc(1, ft_strlen(tmp));
	it = -1;
	while (tmp[++it])
	{
		output[it] = ft_tolower(tmp[it]);
	}
	free(tmp);
	output[it] = '\0';
	return (output);
}

static int		exec_export(t_shell *shell)
{
	int ret;

	ret = 0;
	delete_environment(shell, "_", shell->env);
	ret = ft_export(shell, NULL);
	return (ret);
}

static int		exec_env(t_shell *shell)
{
	char	*lower;
	char	*path;
	char	*tmp;

	lower = to_lower(shell->args[0]);
	if (ft_strcmp(lower, "env"))
	{
		path = get_path(shell);
		tmp = ft_strjoin("_=", path);
		free(path);
		ft_export(shell, tmp);
		free(tmp);
		free(lower);
		return (ft_env(shell, shell->env));
	}
	free(lower);
	return (0);
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
		ret = ft_pwd();
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

static char		*post_to_token(t_shell *shell, char *line, int it, char token)
{
	char	*key;
	char	*value;
	char	*tmp;

	if (token == '>')
		while (line[it++])
			if (line[it] == '}' && line[it - 1] != ' ')
			{
				key = get_var_key(line, it);
				value = expand_var(key, shell);
				if (contain_spaces(value))
				{
					free(value);
					tmp = ft_strjoin("$", key);
					free(key);
					return (tmp);
				}
				free(key);
				free(value);
			}
	return (NULL);
}

static short	prior_to_token(char *line, int it, char token)
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
	{
		return (aux_it < 1 ||
				line[aux_it] == ';' ||
				line[aux_it] == '>' ||
				line[aux_it] == '<' ||
				line[aux_it] == '|');
	}
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

static int		get_validator_err(t_shell *shell,
		char *line, char separator, int it)
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
	shell->stat_loc = 2;
	return (1);
}

static void		safe_print_err(t_shell *shell, char *key)
{
	char	*tmp;

	tmp = ft_strjoin(key, ": ambiguous redirect");
	print_errors(shell, tmp, NULL);
	free(tmp);
	free(key);
}

static int		validator(t_shell *shell, char *line, char separator, int it)
{
	char	*key;

	if (prior_to_token(line, it - 1, line[it]))
	{
		if (get_validator_err(shell, line, separator, it))
			return (1);
		return (0);
	}
	else if (separator == '|' && nothing_after_pipe(&line[it + 1], it))
	{
		print_errors(shell,
				"line 1: syntax error: unexpected end of file", NULL);
		shell->stat_loc = 2;
		return (1);
	}
	else if ((key = post_to_token(shell, line, it, line[it])))
	{
		safe_print_err(shell, key);
		shell->stat_loc = 1;
		return (1);
	}
	return (0);
}

static int		validate_input(t_shell *shell, char *line)
{
	int it;

	it = -1;
	while (line[++it])
	{
		if (line[it] == '|' ||
			line[it] == '<' ||
			line[it] == '>' ||
			line[it] == ';')
		{
			if (validator(shell, line, line[it], it))
				return (0);
		}
	}
	return (1);
	if (line[it + 1] == '<' || line[it + 1] == '>')
		it++;
}

static char		*add_space(char *line, char *output, size_t *it, char redir)
{
	if (line[*it] == redir)
	{
		ft_strlcat(output, line, ft_strlen(output) + *it + 1);
		if (line[*it - 1] != ' ' && line[*it - 1] != redir)
			ft_strlcat(output, " ", ft_strlen(output) + 2);
		ft_strlcat(output, line + *it, ft_strlen(output) + 2);
		if (line[*it + 1] != ' ' && line[*it + 1] != redir)
			ft_strlcat(output, " ", ft_strlen(output) + 2);
		line = line + *it + 1;
		*it = -1;
	}
	return (line);
}

static size_t	additional_spaces(char *line)
{
	size_t	cont;
	size_t	it;

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
	return (cont);
}

static char		*inject_spaces(char *line)
{
	size_t	it;
	size_t	cont;
	char	*output;

	it = -1;
	cont = additional_spaces(line);
	output = calloc(1, ft_strlen(line) + cont + 1);
	while (*line == ' ')
		line++;
	while (line[++it])
	{
		line = add_space(line, output, &it, '>');
		line = add_space(line, output, &it, '<');
	}
	ft_strlcat(output, line, line - output);
	return (output);
}

static char		*safe_allocate(char *line, char *(*f)(char *))
{
	char	*tmp;
	char	*aux;

	tmp = f(line);
	free(line);
	aux = ft_strdup(tmp);
	free(tmp);
	return (aux);
}

static void		minishell(char *line, t_shell *shell)
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

static void		read_input(char *line, t_shell *shell)
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
		if (tmp)
		{
			line = tmp;
			minishell(line, shell);
		}
		else
			shell->stat_loc = 2;
	}
}

static void		exec_argument(char *line, t_shell *shell)
{
	char	*tmp;

	tmp = parse_input(line);
	free(line);
	if (tmp)
	{
		line = tmp;
		minishell(line, shell);
	}
	else
	{
		shell->stat_loc = 2;
	}
	clean_env(shell);
	clean_matrix(shell->instructions);
	free(shell->instructions);
}

int				main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*line;
	char	*tmp;
	char	curr_pwd[1024];

	line = NULL;
	shell.stat_loc = 0;
	shell.instructions = NULL;
	shell.env = ft_strdup_matrix(envp);
	getcwd(curr_pwd, 1024);
	tmp = ft_strjoin("PWD=", curr_pwd);
	ft_export(&shell, tmp);
	free(tmp);
	handle_shlvl(&shell);
	tmp = ft_strdup("_=/bin/bash");
	ft_export(&shell, tmp);
	free(tmp);
	if (argc == 3 && ft_strcmp(argv[1], "-c"))
		exec_argument(ft_strdup(argv[2]), &shell);
	else
		read_input(line, &shell);
	return (shell.stat_loc);
}
