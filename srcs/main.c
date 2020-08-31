#include "minishell.h"

static char 	*get_path(char **args, char **env)
{
	(void)args;
	(void)env;
	char *path;
	
	path = "/bin/ls";
	return (path);		
}

static int		run_command(char **args, char **env)
{
	char 	*path;
	
	path = get_path(args, env);
	if (fork() == 0)
		execve(path, args, env);
	wait(NULL);
	return (1);
}

static int		check_builtin(char **args, char **env)
{
	/*if (ft_strcmp(*args, "echo"))
	{
		
	}
	else if (ft_strcmp(*args, "cd"))
	{
		
	}
	else if(ft_strcmp(*args, "pwd"))
	{
		
	}
	else if (ft_strcmp(*args, "export"))
	{
		
	}
	else if (ft_strcmp(*args, "unset"))
	{
		
	}
	else if (ft_strcmp(*args, "env"))
	{
		
	}*/
	//if (ft_strncmp(*args, "exit", ft_strlen("exit")))
	//	return (0);
	//else
		run_command(args, env);
	return (0);
}

static void	minishell(char **env)
{
	int 	status;
	char 	*line;
	char 	**args;

	status = 1;
	while (status)
	{
		ft_putstr_fd("minishell:\\>", 1);
		get_next_line(0, &line);
		args = get_args(line);
		check_builtin(args, env);
		//status = ft_ctrld();
	}
}

int main(int argc, char **argv, char **envp)
{	
	(void)argc;
	(void)argv;
	minishell(envp);
	return (0);
}
