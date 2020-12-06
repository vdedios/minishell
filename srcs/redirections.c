#include "minishell.h"

static	int	redirections_append(t_shell *shell, size_t it, char exited)
{
	int fd;
	
	if (!(shell->args[it + 1]))
	{
		shell->stat_loc = 2;
		print_errors(shell, "syntax error near unexpected token `newline'", NULL, exited);
	}
	if ((fd = open(shell->args[it + 1], O_CREAT | O_APPEND | O_WRONLY, 0644)) == -1)
	{
		shell->stat_loc = 1;
		print_errors(shell, " No such file or directory", shell->args[it + 1], exited);
	}
	else
		dup2(fd, 1);
	ft_unset(shell->args[it], shell->args);
	ft_unset(shell->args[it], shell->args);
	return (fd);
}

static int	redirections_output(t_shell *shell, size_t it, char exited)
{	
	int fd;

	if (!(shell->args[it + 1]))
	{
		shell->stat_loc = 2;
		print_errors(shell, "syntax error near unexpected token `newline'", NULL, exited);
	}
	if ((fd = open(shell->args[it + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
	{
		shell->stat_loc = 1;
		print_errors(shell, " No such file or directory", shell->args[it + 1], exited);
	}
	else
		dup2(fd, 1);
	ft_unset(shell->args[it], shell->args);
	ft_unset(shell->args[it], shell->args);
	return (fd);
}

static int	redirections_input(t_shell *shell, size_t it, char exited)
{
	int fd;
	struct stat	s;

	fd = -1;
	if (!(shell->args[it + 1]))
	{
		shell->stat_loc = 2;
		print_errors(shell, "syntax error near unexpected token `newline'", NULL, exited);
	}
	if ((fd = open(shell->args[it + 1], O_RDONLY, 0644)) == -1)
	{
		if (stat(shell->args[it + 1], &s) != -1)
		{
			if (!(s.st_mode & S_IRUSR) || (s.st_mode & S_IRUSR && (!(s.st_mode & S_IXUSR))))
			{
				shell->stat_loc = 1;
				print_errors(shell, " Permission denied", shell->args[it + 1], exited);
			}
		}
		else
		{
			shell->stat_loc = 1;
			print_errors(shell, " No such file or directory", shell->args[it + 1], exited);
		}
	}
	else
		dup2(fd, 0);
	ft_unset(shell->args[it], shell->args);
	ft_unset(shell->args[it], shell->args);
	return (fd);
}

int	find_redirections(t_shell *shell, char exited)
{
	size_t 	it;
	int		fd;
	
	it = 0;
	fd = -5;
	while (shell->args[it])
	{
		if (ft_strcmp(shell->args[it], ">"))
			fd = redirections_output(shell, it, exited);
		else if (ft_strcmp(shell->args[it], "<"))
			fd = redirections_input(shell, it, exited);
		else if (ft_strcmp(shell->args[it], ">>"))
			fd = redirections_append(shell, it, exited);
		else
			it++;
	}
	return (fd);
}
