#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include "libft.h"

/*
** Basic structures
*/

typedef struct	s_expand{
	char		*pre;
	char		*env;
	char		*post;
}				t_expand;

typedef struct	s_shell{
	char		**instructions;
	char		*binary;
	char		**commands;
	char		**args;
	char		**env;
	int			stat_loc;
}				t_shell;


/*
** Cleaning functions
*/

void	clean_matrix(char **matrix);
void	clean_commands(t_shell *shell);
void	clean_env(t_shell *shell);
void	clean_shell(t_shell *shell);


/*
** Error functions
*/

void	print_errors(t_shell *shell, char *msg, char *bin, char exited);


/*
** Utils functions
*/

char	**ft_strdup_matrix(char **envp);
char	*absolute_bin_path(char *path, char *bin);
char	**add_env(char **variable, char **env, int n);
char	**realloc_matrix(char **envp, int additional);
char	**get_args(char *input);
char	*get_env(char **env, char *arg);
char	*search_binary(char *binary, char **paths);
int		get_next_line(char **line);
int		find_redirections(t_shell *shell, char exited);
void	find_pipes(t_shell *shell);
int		check_builtin(t_shell *shell);
int		run_command(t_shell *shell, char exited);

/*
** Parsing functions
*/

void	expansion(t_shell *shell);

/*
** Builtin functions
*/

int		ft_env(char **args, char **env);
int		ft_cd(t_shell *shell);
int		ft_echo(char **args);
int		ft_pwd();
int		ft_unset(char *var, char **env);
void	ft_exit(t_shell *shell);
int 	ft_export(t_shell *shell);

/*
** Signal functions
*/

void	signal_handler_waiting(int signal);
void	signal_handler_running(int signal);

#endif
