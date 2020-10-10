#include "minishell.h"

static	int	redirections_append(t_shell *shell, size_t it)
{
	int fd;
	
	fd = open(shell->args[it + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	ft_unset(shell->args[it], shell->args);
	ft_unset(shell->args[it], shell->args);
	dup2(fd, 1);
	return (fd);
}

static int	redirections_output(t_shell *shell, size_t it)
{	
	int fd;
	
	fd = open(shell->args[it + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	ft_unset(shell->args[it], shell->args);
	ft_unset(shell->args[it], shell->args);
	dup2(fd, 1);
	return (fd);
}

static int	redirections_input(t_shell *shell, size_t it)
{
	int fd;
	
	fd = open(shell->args[it + 1], O_RDONLY, 0644);
	ft_unset(shell->args[it], shell->args);
	ft_unset(shell->args[it], shell->args);
	dup2(fd, 0);
	return (fd);
}

int	find_redirections(t_shell *shell)
{
	size_t 	it;
	int		fd;
	
	it = 0;
	while (shell->args[it])
	{
		if (ft_strcmp(shell->args[it], ">"))
			fd = redirections_output(shell, it);
		else if (ft_strcmp(shell->args[it], "<"))
			fd = redirections_input(shell, it);
		else if (ft_strcmp(shell->args[it], ">>"))
			fd = redirections_append(shell, it);
		//else if (ft_strcmp(shell->arg, "|"))
		//	redirection_pipe();	
		else
			it++;
	}
	return (fd);
}
