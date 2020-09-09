#include "minishell.h"

void	signal_handler(int signal)
{
	ft_putendl_fd("\nCaught signal", 1);
	ft_putnbr_fd(signal, 1);
	exit(1);
}
