/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:42:50 by schahir           #+#    #+#             */
/*   Updated: 2025/02/10 20:36:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(t_pipex *pipex, char **av, char **envp)
{
	char	*a;
	char	*b;

	pipex->av = av;
	pipex->envp = envp;
	pipex->cmd1 = ft_split(av[2], ' ');
	if (!pipex->cmd1 || !pipex->cmd1[0] || pipex->cmd1[0][0] == '\0')
	{
		ft_printf("pipex: invalid command: %s\n", av[2]);
		exit(1);
	}
	pipex->cmd2 = ft_split(av[3], ' ');
	if (!pipex->cmd2 || !pipex->cmd2[0] || pipex->cmd2[0][0] == '\0')
	{
		ft_free_split(pipex->cmd1);
		ft_printf("pipex: invalid command: %s\n", av[3]);
		exit(1);
	}
	get_env(pipex);
	a = pipex->cmd1[0];
	b = pipex->cmd2[0];
	pipex->cmd1[0] = get_path(pipex, a);
	if (!pipex->cmd1[0])
	{
		ft_printf("pipex: command not found: %s\n", a);
		ft_free(pipex);
		exit(127);
	}
	pipex->cmd2[0] = get_path(pipex, b);
	if (!pipex->cmd2[0])
	{
		ft_printf("pipex: command not found: %s\n", b);
		ft_free(pipex);
		exit(127);
	}
	if (a != pipex->cmd1[0])
		free(a);
	if (b != pipex->cmd2[0])
		free(b);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5 || !av[2][0] || !av[3][0])
	{
		ft_printf("Invalid input.\n");
		exit(1);
	}
	ft_init(&pipex, av, envp);
	ft_open(&pipex);
	ft_cmd1(&pipex);
	ft_cmd2(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	ft_free(&pipex);
	return (0);
}
