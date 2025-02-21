/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:42:54 by schahir           #+#    #+#             */
/*   Updated: 2025/02/12 22:40:40 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
void	ft_free(t_pipex *pipex)
{
	int	i;

	if (pipex->cmds)
	{
		i = 0;
		while (i < pipex->num_cmds)
		{
			ft_free_split(pipex->cmds[i]);
			i++;
		}
		free(pipex->cmds);
	}
	if (pipex->env)
		ft_free_split(pipex->env);
	if (pipex->pids)
		free(pipex->pids);
}
