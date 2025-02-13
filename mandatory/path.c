/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schahir <schahir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:07:35 by schahir           #+#    #+#             */
/*   Updated: 2025/02/12 21:06:24 by schahir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_env(t_pipex *pipex)
{
	int		i;
	char	*path_var;
	char	*path;

	i = 0;
	while (pipex->envp[i] && ft_strncmp(pipex->envp[i], "PATH=", 5) != 0)
		i++;
	if (!pipex->envp[i])
	{
		pipex->env = NULL;
		return ;
	}
	path_var = pipex->envp[i];
	path = ft_strchr(path_var, '=');
	if (!path)
	{
		pipex->env = NULL;
		return ;
	}
	path++;
	pipex->env = ft_split(path, ':');
}

char	*get_path(t_pipex *pipex, char *command)
{
	int		i;
	char	*str;
	char	*cmd;
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	if (!pipex->env)
		return (NULL);
	i = -1;
	while (pipex->env[++i])
	{
		str = ft_strjoin(pipex->env[i], "/");
		if (!str)
			return (NULL);
		cmd = ft_strjoin(str, command);
		free(str);
		if (!cmd)
			return (NULL);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
	}
	return (NULL);
}
