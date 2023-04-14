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

void	ft_parentpro(int file2, char **av, char **envp, int *pipe)
{
	char *paths;
	char **split_paths;
	char **cmd_args;
	char *cmd;
	int i;

	i = 0;
	if(dup2(file2, STDOUT_FILENO) < 0 || dup2(pipe[0], 0) < 0)
		exit(0);
	close(pipe[1]);
	paths = ft_getPaths(envp);
	split_paths = ft_split(paths, ':');
	split_paths = ft_appendChar(split_paths, "/");
	cmd_args = ft_split(av[3], ' ');
	while(split_paths[i++])
	{
		cmd = ft_strjoin(split_paths[i], cmd_args[0]);
		if(access(cmd, X_OK) == 0)
			execve(cmd, cmd_args, envp);
		free(cmd);
	}
	perror("Child Process Error");
}



void	ft_childpro(int file1, char **av, char **envp, int *pipe)
{
	char *paths;
	char **split_paths;
	char **cmd_args;
	char *cmd;
	int i;

	i = 0;
	if(dup2(file1, STDIN_FILENO) < 0 || dup2(pipe[1], 1) < 0)
		exit(0);
	close(pipe[0]);
	paths = ft_getPaths(envp);
	split_paths = ft_split(paths, ':');
	split_paths = ft_appendChar(split_paths, "/");
	cmd_args = ft_split(av[2], ' ');
	while(split_paths[i++])
	{
		cmd = ft_strjoin(split_paths[i], cmd_args[0]);
		execve(cmd, cmd_args, envp);
		free(cmd);
	}
	perror("Child Process Error");
}