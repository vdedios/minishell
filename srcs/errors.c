#include "minishell.h"

void	print_errors(char *msg, char *bin)
{
	ft_putstr_fd("$:\\>", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd(bin, 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}
