#include "pipex_bonus.h"

void handle_here_doc(t_pipex *pipex, char *limiter_arg)
{
    int     here_pipe[2];
    char    *line;
    char    *limiter;

    limiter = ft_strjoin(limiter_arg, "\n");
    if (!limiter)
        exit(1);
    if (pipe(here_pipe) == -1)
    {
        ft_putstr_fd("Error: pipe creation failed\n", 2);
        free(limiter);
        ft_free(pipex);
        exit(1);
    }
    ft_putstr_fd("heredoc> ", 1);
    while (1)
    {
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;
        if (ft_strcmp(line, limiter) == 0)
        {
            free(line);
            break;
        }
        write(here_pipe[1], line, ft_strlen(line));
        free(line);
        ft_putstr_fd("heredoc> ", 1);
    }
    free(limiter);
    close(here_pipe[1]);
    pipex->fd1 = here_pipe[0];
    
    pipex->fd2 = open(pipex->av[pipex->num_cmds + 3], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (pipex->fd2 == -1)
    {
        close(here_pipe[0]);
        perror("pipex: output file");
        ft_free(pipex);
        exit(1);
    }
}
