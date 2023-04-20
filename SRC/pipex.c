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

void	ex_child(char *av, char **env, t_pipex pipex)
{
	int id;
	
	pipe(pipex.pipe);
	id = fork();
	if(id == 0)
	{
		close(pipex.pipe[0]);
		dup2(pipex.pipe[1], 1);
		ft_exec(av, env);
	}
	else
	{
		wait(&id);
		close(pipex.pipe[1]);
		dup2(pipex.pipe[0], 0);
	}
}

void	pipex(int ac, char **av, char **envp, t_pipex pipex)
{
	int	i;
	if(ft_strcmp(av[1], "here_doc") == 0)
		i = 3;
	else
	{
		i = 2;
		dup2(pipex.fd1, 0);
	}
	while(i < ac -2)
	{
		ex_child(av[i], envp, pipex);
		i++;
	}
	dup2(pipex.fd2, 1);
	ft_exec(av[ac - 2], envp);
}

void	open_files(t_pipex pipe, int type, char **av, int ac)
{
	if(type == 1)
	{
		pipe.fd1 = open(av[1], O_RDONLY);
		pipe.fd2 = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
		
		if(pipe.fd1 < 0 || pipe.fd2 < 0)
			ft_error(1);
	}
	if(type == 2)
	{}
}


int main(int ac, char **av, char **envp)
{
	t_pipex pipe;

	if(ac > 5)
	{
		if(ft_strcmp(av[1], "here_doc") == 0)
		{

		}
		pipex(ac, av, envp, pipe);
	}
	else
		ft_error(0);


}


// int main()
// {
//     char lol[] = "cat";
//     char **ok;

//     ok = ft_cmd_split(lol, ' ');
   
//         printf("%s\n", ok[0]);
    
//     return (0);
// }