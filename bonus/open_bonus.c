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

void ft_open(t_pipex *pipex, int ac)
{
    if (pipex->here_doc)
    {
        if (pipex->fd2 <= 0)
        {
            pipex->fd2 = open(pipex->av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (pipex->fd2 == -1)
            {
                perror("pipex: output file");
                exit(1);
            }
        }
    }
    else
    {
        pipex->fd1 = open(pipex->av[1], O_RDONLY);
        if (pipex->fd1 == -1)
        {
            perror("pipex: input file");
            exit(1);
        }
        pipex->fd2 = open(pipex->av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (pipex->fd2 == -1)
        {
            close(pipex->fd1);
            perror("pipex: output file");
            exit(1);
        }
    }
}
