/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkpros.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:36:04 by mneri             #+#    #+#             */
/*   Updated: 2023/04/14 16:36:06 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freepath(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
}

void	ft_error(int error)
{
	if (error == 0)
		perror("Error! Wrong number of arguments");
	else if (error == 1)
		perror("pipe() Error!");
	else if (error == 2)
		perror("fork() Error!");
	else if (error == 3)
		perror("file Error!");
	else if (error == 4)
		perror("dup2() Error!");
	else if (error == 6)
		perror("cmd Error!");
	else if (error == 7)
		perror("path Error!");
	else if (error == 8)
		perror("execve() Error!");
	exit(127);
}

char	*ft_path(char **env, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*tmp;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_freepath(paths);
	return (NULL);
}

void	ft_exec(char *av, char **env)
{
	char	*path;
	char	**cmd;

	cmd = ft_pipe_split(av, ' ');
	if (cmd == NULL)
		ft_error(6);
	path = ft_path(env, cmd[0]);
	if (!path)
	{
		ft_freepath(cmd);
		free(path);
		ft_error(7);
	}
	if (execve(path, cmd, env) < 0)
		ft_error(8);
	free(path);
	ft_freepath(cmd);
}
