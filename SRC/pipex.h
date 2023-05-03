/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:49:00 by mneri             #+#    #+#             */
/*   Updated: 2023/05/03 14:49:01 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../ft_printf/ft_printf.h"
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	int	fd1;
	int	fd2;
	int	pipe[2];
	int	here_doc;
}	t_pipex;

char	*ft_path(char **env, char *cmd);
void	ft_exec(char *av, char **env);
char	*ft_getPaths(char **envp);
void	ft_error(int error);
char	**ft_pipe_split(char *s, char c);

#endif