/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:28:53 by schahir           #+#    #+#             */
/*   Updated: 2025/02/13 14:12:11 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_open(t_pipex *pipex, int ac)
{
	pipex->fd1 = open(pipex->av[1], O_RDONLY);
	pipex->fd2 = open(pipex->av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
