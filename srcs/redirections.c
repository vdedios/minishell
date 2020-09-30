#include "minishell.h"

void	redirections_append(t_shell *shell, size_t it)
{
	int fd;
	
	fd = open(shell->args[it + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	dup2(fd, 1);
}

static void	redirections_output(t_shell *shell, size_t it)
{	
	int fd;
		
	fd = open(shell->args[it + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	dup2(fd, 1);
}

void	redirections_input(t_shell *shell, size_t it)
{
	int fd;
	
	fd = open(shell->args[it + 1], O_RDONLY, 0644);
	dup2(fd, 0);
}

void	find_redirections(t_shell *shell)
{
	size_t it;
	
	it = -1;
	while (shell->args[++it])
	{
		if (ft_strcmp(shell->args[it], ">"))
			redirections_output(shell, it);
		else if (ft_strcmp(shell->args[it], "<"))
			redirections_input(shell, it);
		else if (ft_strcmp(shell->args[it], ">>"))
			redirections_append(shell, it);
		//else if (ft_strcmp(shell->arg, "|"))
		//	redirection_pipe();	
		ft_unset(shell->args[it], shell->args);
		ft_unset(shell->args[it], shell->args);
	}
}
