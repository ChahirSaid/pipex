/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:28:53 by schahir           #+#    #+#             */
/*   Updated: 2025/02/10 20:37:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open(t_pipex *pipex)
{
	pipex->fd1 = open(pipex->av[1], O_RDONLY);
	if (pipex->fd1 == -1)
	{
		ft_printf("pipex: infile");
		ft_free(pipex);
		exit(1);
	}
	pipex->fd2 = open(pipex->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd2 == -1)
	{
		close(pipex->fd1);
		ft_printf("pipex: outfile");
		ft_free(pipex);
		exit(1);
	}
	if (pipe(pipex->pipefd) == -1)
	{
		close(pipex->fd1);
		close(pipex->fd2);
		ft_printf("pipex: pipe");
		ft_free(pipex);
		exit(1);
	}
}