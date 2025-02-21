/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:42:50 by schahir           #+#    #+#             */
/*   Updated: 2025/02/13 15:17:57 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void ft_init(t_pipex *pipex, int ac, char **av, char **envp)
{
    int     i;
    char    *a;
    int     av_idx;

    pipex->av = av;
    pipex->envp = envp;
    pipex->here_doc = 0;
    if (ac > 1 && ft_strcmp(av[1], "here_doc") == 0)
    {
        pipex->here_doc = 1;
        pipex->num_cmds = ac - 4;
    }
    else
        pipex->num_cmds = ac - 3;
    pipex->cmds = malloc(sizeof(char **) * pipex->num_cmds);
    if (!pipex->cmds)
        exit(1);
    get_env(pipex);
    i = 0;
    while (i < pipex->num_cmds)
    {
        if (pipex->here_doc)
            av_idx = 3 + i;
        else
            av_idx = 2 + i;
        pipex->cmds[i] = cmd_split(av[av_idx]);
        if (!pipex->cmds[i] || !pipex->cmds[i][0] || pipex->cmds[i][0][0] == '\0')
        {
            perror("pipex: invalid command");
            for (int j = 0; j < i; j++)
                ft_free_split(pipex->cmds[j]);
            if (pipex->cmds[i])
                ft_free_split(pipex->cmds[i]);
            free(pipex->cmds);
            ft_free_split(pipex->env);
            exit(1);
        }
        a = pipex->cmds[i][0];
        pipex->cmds[i][0] = get_path(pipex, a);
        if (!pipex->cmds[i][0])
        {
            perror("pipex: command not found");
            for (int j = 0; j <= i; j++)
                ft_free_split(pipex->cmds[j]);
            free(pipex->cmds);
            ft_free_split(pipex->env);
            exit(127);
        }
        if (a != pipex->cmds[i][0])
            free(a);
        i++;
    }
}

int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;
	int		prev_pipe;
	int		i;
	int     pipefd[2];
	int		status;

	if (ac < 5 || (ft_strcmp(av[1], "here_doc") == 0 && ac < 6))
	{
		ft_putstr_fd("Invalid number of arguments\n", STDERR_FILENO);
		exit(1);
	}
	ft_init(&pipex, ac, av, envp);
    
    if (pipex.here_doc)
        handle_here_doc(&pipex, av[2]);
    else
		ft_open(&pipex, ac);
	prev_pipe = -1;
	pipex.pids = malloc(sizeof(pid_t) * pipex.num_cmds);
	i = 0;
	while (i < pipex.num_cmds)
	{
		if (i < pipex.num_cmds - 1 && pipe(pipefd) == -1)
		{
			close(pipex.fd1);
			close(pipex.fd2);
			perror("pipex: pipe");
			ft_free(&pipex);
			exit(1);
		}
		pipex.pids[i] = fork();
		if (pipex.pids[i] == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pipex.pids[i] == 0)
		{
			if (i > 0)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			else
				dup2(pipex.fd1, STDIN_FILENO);
			if (i < pipex.num_cmds - 1)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			else
				dup2(pipex.fd2, STDOUT_FILENO);
			close(pipefd[0]);
			execve(pipex.cmds[i][0], pipex.cmds[i], envp);
			perror("execve");
			exit(1);
		}
		else
		{
			if (i > 0)
				close(prev_pipe);
			if (i < pipex.num_cmds - 1)
			{
				prev_pipe = pipefd[0];
				close(pipefd[1]);
			}
		}
		i++;
	}
	close(pipex.fd1);
	close(pipex.fd2);
	i = 0;
	while (i < pipex.num_cmds)
	{
		waitpid(pipex.pids[i], &status, 0);
		i++;
	}
	ft_free(&pipex);
	exit(WEXITSTATUS(status));
}
