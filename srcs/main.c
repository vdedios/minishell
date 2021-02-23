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
			clean_env(shell);
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
		clean_instructions(shell);
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
