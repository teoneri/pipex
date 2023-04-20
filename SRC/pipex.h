#include "../ft_printf/ft_printf.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_pipe
{
	int fd1;
	int fd2;
	int pipe[2];
	int here_doc;
} t_pipex;


char	*ft_path(char **env, char *cmd);
void ft_exec(char *av, char **env);
char *ft_getPaths(char **envp);
void   ft_error(int error);
char	**ft_cmd_split(const char *s, char c);
