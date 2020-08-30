#include "minishell.h"

static void	minishell(void)
{
	int 	status;
	char 	*line;

	status = 1;
	while (status)
	{
		ft_putstr_fd("minishell:\\>", 1);
		get_next_line(0, &line);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	minishell();
	return (0);
}
