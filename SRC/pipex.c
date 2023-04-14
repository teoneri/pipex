/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:11:19 by mneri             #+#    #+#             */
/*   Updated: 2023/04/06 14:11:21 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char **ft_appendChar(char **str, char *c)
{
	char **appended = str;
	while(*str)
	{
		ft_strjoin(*str, c);
		str++;
	}
	str = appended;
	return str;
}

char *ft_getPaths(char **envp)
{
	char *paths;

	while(envp)
	{
		if(!ft_strncmp("PATH", *envp, 4))
			break;
		envp++;
	}
	paths = *envp + 5;
	return(paths);
}

int main(int ac, char **av, char **envp)
{
	int file1;
	int file2;
	int id;
	int pipeid[2];
	if(ac != 5)
	{
		perror("args error");
		return 1;
	}
	file1 = open(av[1], O_RDONLY);
	file2 = open(av[4], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if(file1 < 0)
		perror("file error");
	pipe(pipeid);
	id = fork();
	if(id == 0)
		ft_childpro(file1, av, envp, pipeid);
	else
		ft_parentpro(file2, av, envp, pipeid);
}