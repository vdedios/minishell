#include "minishell.h"

/*
typedef struct	s_shell{
	char		**commands;
	char		**args;
	char		**env;
	int			stat_loc;
}				t_she
*/

void	clean_matrix(char **matrix)
{
	while (*matrix)
	{
		free(*matrix);
		matrix++;
	}
}

void	clean_shell(t_shell *shell)
{
	clean_matrix(shell->commands);
	free(shell->commands);
	clean_matrix(shell->args);
	free(shell->args);
}
