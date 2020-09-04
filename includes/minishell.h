#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <errno.h>
# include <dirent.h>
# include "get_next_line_bonus.h"

char	**get_args(char *input);
char	*get_path(char *arg, char **env);

#endif
