/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:44:02 by schahir           #+#    #+#             */
/*   Updated: 2025/02/10 20:35:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd1(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		ft_close_fd(pipex);
		ft_printf("pipex: fork");
		ft_free(pipex);
		exit(1);
	}
	if (pipex->pid1 == 0)
	{
		close(pipex->pipefd[0]);
		dup2(pipex->pipefd[1], STDOUT_FILENO);
		close(pipex->pipefd[1]);
		dup2(pipex->fd1, STDIN_FILENO);
		close(pipex->fd1);
		if (execve(pipex->cmd1[0], pipex->cmd1, pipex->envp) == -1)
		{
			ft_printf("pipex: execve");
			ft_close_fd(pipex);
			ft_free(pipex);
			exit(1);
		}
	}
	close(pipex->pipefd[1]);
	close(pipex->fd1);
}

void	ft_cmd2(t_pipex *pipex)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		ft_close_fd(pipex);
		ft_printf("pipex: fork");
		ft_free(pipex);
		exit(1);
	}
	if (pipex->pid2 == 0)
	{
		close(pipex->pipefd[1]);
		dup2(pipex->pipefd[0], STDIN_FILENO);
		close(pipex->pipefd[0]);
		dup2(pipex->fd2, STDOUT_FILENO);
		close(pipex->fd2);
		if (execve(pipex->cmd2[0], pipex->cmd2, pipex->envp) == -1)
		{
			ft_printf("pipex: execve");
			ft_close_fd(pipex);
			ft_free(pipex);
			exit(1);
		}
	}
	close(pipex->fd2);
	close(pipex->pipefd[0]);
}
