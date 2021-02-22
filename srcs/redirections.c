/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:01:20 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 15:27:40 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		redirections_append(t_shell *shell, size_t it)
{
	int fd;

	fd = -1;
	if (!(shell->args[it + 1]))
	{
		shell->stat_loc = 2;
		print_errors(shell,
				"syntax error near unexpected token `newline'", NULL);
	}
	else
	{
		if ((fd = open(shell->args[it + 1],
						O_CREAT | O_APPEND | O_WRONLY, 0644)) == -1)
		{
			shell->stat_loc = 1;
			print_errors(shell,
					" No such file or directory", shell->args[it + 1]);
		}
		else
			dup2(fd, 1);
		delete_environment(shell, shell->args[it], shell->args);
	}
	delete_environment(shell, shell->args[it], shell->args);
	return (fd);
}

static int		redirections_output(t_shell *shell, size_t it)
{
	int fd;

	fd = -1;
	if (!(shell->args[it + 1]))
	{
		shell->stat_loc = 2;
		print_errors(shell,
				"syntax error near unexpected token `newline'", NULL);
	}
	else
	{
		if ((fd = open(shell->args[it + 1],
						O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		{
			shell->stat_loc = 1;
			print_errors(shell,
					" No such file or directory", shell->args[it + 1]);
		}
		else
			dup2(fd, 1);
		delete_environment(shell, shell->args[it], shell->args);
	}
	delete_environment(shell, shell->args[it], shell->args);
	return (fd);
}

static short	redirection_exists(t_shell *shell, size_t it)
{
	struct stat	s;
	int			fd;

	fd = -1;
	if ((fd = open(shell->args[it + 1], O_RDONLY, 0644)) == -1)
	{
		if (stat(shell->args[it + 1], &s) != -1)
		{
			if (!(s.st_mode & S_IRUSR) ||
					(s.st_mode & S_IRUSR && (!(s.st_mode & S_IXUSR))))
			{
				shell->stat_loc = 1;
				print_errors(shell, " Permission denied", shell->args[it + 1]);
			}
		}
		else
		{
			shell->stat_loc = 1;
			print_errors(shell,
					" No such file or directory", shell->args[it + 1]);
		}
	}
	return (fd);
}

static int		redirections_input(t_shell *shell, size_t it)
{
	int fd;

	fd = -1;
	if (!(shell->args[it + 1]))
	{
		shell->stat_loc = 2;
		print_errors(shell,
				"syntax error near unexpected token `newline'", NULL);
	}
	else
	{
		if ((fd = redirection_exists(shell, it)) != -1)
			dup2(fd, 0);
		delete_environment(shell, shell->args[it], shell->args);
	}
	delete_environment(shell, shell->args[it], shell->args);
	if (it == 0 && shell->args[0])
	{
		free(shell->binary);
		shell->binary = ft_strdup(shell->args[0]);
	}
	return (fd);
}

static int		validate_count(t_shell *shell
							, size_t cont_output, size_t cont_input)
{
	char	*msg;

	msg = NULL;
	if (cont_output > 2)
	{
		if (cont_output < 4)
			msg = ft_strjoin("syntax error near unexpected token `",
					">'");
		else
			msg = ft_strjoin("syntax error near unexpected token `",
					">>'");
		print_errors(shell, msg, NULL);
		free(msg);
		shell->stat_loc = 2;
		return (0);
	}
	if (cont_input > 2)
	{
		msg = ft_strjoin("syntax error near unexpected token `",
				"<<'");
		print_errors(shell, msg, NULL);
		free(msg);
		shell->stat_loc = 2;
		return (0);
	}
	return (1);
}

static int		validator(t_shell *shell, char *str)
{
	size_t	cont_output;
	size_t	cont_input;

	cont_output = 0;
	cont_input = 0;
	while (*str)
	{
		if (*str == '>')
			cont_output++;
		else if (*str == '<')
			cont_input++;
		else if (*str != ' ')
		{
			cont_output = 0;
			cont_input = 0;
		}
		str++;
	}
	if (!(validate_count(shell, cont_output, cont_input)))
		return (0);
	return (1);
}

int				find_redirections(t_shell *shell)
{
	size_t	it;
	int		fd;

	it = 0;
	fd = -5;
	while (shell->args[it])
	{
		if (validator(shell, shell->args[it]))
		{
			if (ft_strcmp(shell->args[it], ">"))
				fd = redirections_output(shell, it);
			else if (ft_strcmp(shell->args[it], "<"))
				fd = redirections_input(shell, it);
			else if (ft_strcmp(shell->args[it], ">>"))
				fd = redirections_append(shell, it);
			else
				it++;
		}
		else
		{
			fd = -1;
			break ;
		}
	}
	close(fd);
	return (fd);
}
