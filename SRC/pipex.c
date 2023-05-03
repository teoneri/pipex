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
	int	id;

	pipe(pipex.pipe);
	id = fork();
	if (id == 0)
	{
		close(pipex.pipe[0]);
		if (dup2(pipex.pipe[1], 1) < 0)
			ft_error(4);
		ft_exec(av, env);
	}
	else
	{
		wait(&id);
		close(pipex.pipe[1]);
		if (dup2(pipex.pipe[0], 0) < 0)
			ft_error(4);
	}
}

void	pipex(int ac, char **av, char **envp, t_pipex pipex)
{
	int	i;

	if (ft_strcmp(av[1], "here_doc") == 0)
		i = 3;
	else
	{
		i = 2;
		if (dup2(pipex.fd1, 0) < 0)
			ft_error(4);
	}
	while (i < ac -2)
	{
		ex_child(av[i], envp, pipex);
		i++;
	}
	if (dup2(pipex.fd2, 1) < 0)
		ft_error(4);
	ft_exec(av[ac - 2], envp);
}

void	find_lim(char *line, char *limiter, t_pipex pipex)
{
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		exit(EXIT_SUCCESS);
	write(pipex.pipe[1], line, ft_strlen(line));
}

void	here_doc(char *limiter, int ac, t_pipex pipex)
{
	pid_t	reader;
	char	*line;

	if (ac < 5)
		ft_error(0);
	pipe(pipex.pipe);
	reader = fork();
	if (reader == 0)
	{
		close(pipex.pipe[0]);
		while (1)
		{
			line = get_next_line(0);
			if (!line)
				break ;
			find_lim(line, limiter, pipex);
		}
	}
	else
	{
		close(pipex.pipe[1]);
		if (dup2(pipex.pipe[0], STDIN_FILENO) < 0)
			ft_error(4);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipe;

	if (ac >= 5)
	{
		if (ft_strcmp(av[1], "here_doc") == 0)
		{
			pipe.fd2 = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (pipe.fd2 < 0)
				ft_error(1);
			here_doc(av[2], ac, pipe);
			pipex(ac, av, envp, pipe);
		}
		else
		{
			pipe.fd1 = open(av[1], O_RDONLY);
			pipe.fd2 = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (pipe.fd1 < 0 || pipe.fd2 < 0)
				ft_error(1);
			pipex(ac, av, envp, pipe);
		}
	}
	else
		ft_error(0);
}

// int main()
// {
// 	char s[] = "awk '{count++} END {print count}'";
// 	char **s1;

// 	s1 = ft_pipe_split(s, ' ');
// 	int i = 0;
// 	while(i < 2)
// 	{
// 		printf("%s\n", s1[i]);
// 		i++;
// 	}
// }