#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include "libft.h"

typedef struct	s_expand{
	char		*pre;
	char		*env;
	char		*post;
}				t_expand;

typedef struct	s_shell{
	char		**commands;
	char		**args;
	char		**env;
	int			is_env_malloc;
	int			stat_loc;
}				t_shell;

char	**get_args(char *input);
char	*get_env(char **env, char *arg);
char	*search_binary(char *binary, char **paths);
void	expansion(t_shell *shell);
int		ft_env(char **args, char **env);
int		ft_cd(t_shell *shell);
int		ft_echo(char **args);
int		ft_pwd();
int		ft_unset(char *var, char **env);
void	ft_exit(char **exit);
void	signal_handler_waiting(int signal);
void	signal_handler_running(int signal);
int 	ft_export(t_shell *shell);
char	**realloc_matrix(char **envp, int additional);
char	**ft_strdup_matrix(char **envp);
size_t	ft_strcmp(char *s1, char *s2);
int		get_next_line(char **line);
void	print_errors(char *msg, char *bin);
void	clean_shell(t_shell *shell);
char	*abs_bin_path(char *path, char *bin);
void	clean_matrix(char **matrix);
char	**add_env(char *variable, char **env, int n);

#endif
