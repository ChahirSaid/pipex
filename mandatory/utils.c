/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:42:54 by schahir           #+#    #+#             */
/*   Updated: 2025/02/10 20:24:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **str)
{
	int	i;
	
	if(!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
void	ft_free(t_pipex *pipex)
{
	if (pipex->cmd1)
		ft_free_split(pipex->cmd1);
	if (pipex->cmd2)
		ft_free_split(pipex->cmd2);
	if (pipex->env)
		ft_free_split(pipex->env);
}

void	ft_close_fd(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	close(pipex->fd1);
	close(pipex->fd2);
}