#include "minishell.h"

void	print_errors(t_shell *shell, char *msg, char *bin)
{
	ft_putstr_fd("minishell: ", 1);
	if (bin)
	{
		ft_putstr_fd(bin, 1);
		ft_putchar_fd(':', 1);
	}
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	exit(shell->stat_loc);
}
