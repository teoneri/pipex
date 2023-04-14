#include "../ft_printf/ft_printf.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	ft_childpro(int file1, char **av, char **envp, int *pipe);
void	ft_parentpro(int file2, char **av, char **envp, int *pipe);
char *ft_getPaths(char **envp);
char **ft_appendChar(char **str, char *c);
