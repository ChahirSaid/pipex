/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:57:08 by schahir           #+#    #+#             */
/*   Updated: 2025/02/13 15:42:45 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
#include <stdio.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"

typedef struct s_pipex {
    char    **av;
    char    **envp;
    char    ***cmds;
    int     num_cmds;
    char    **env;
    int     fd1;
    int     fd2;
    pid_t   *pids;
}   t_pipex;

void	get_env(t_pipex *pipex);
char	*get_path(t_pipex *pipex, char *command);
void	ft_open(t_pipex *pipex, int ac);
void	ft_free_split(char **str);
void	ft_free(t_pipex *pipex);
void	ft_close_fd(t_pipex *pipex);
char	**cmd_split(char const *s);

#endif