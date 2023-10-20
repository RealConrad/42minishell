/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:26:37 by harsh             #+#    #+#             */
/*   Updated: 2023/10/20 13:52:10 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_infile(t_pip_bonus *pipex)
{
	if (pipex->here_doc_flag == FALSE)
	{
		pipex->infile_fd = open_file(pipex->argv[1]);
		if (pipex->infile_fd < 0)
			error_bonus(ERR_INFILE, pipex->argv[1], pipex);
	}
	dup2(pipex->infile_fd, STDIN_FILENO);
}

void	first_child(t_pip_bonus *pipex)
{
	int	pid;

	if (pipe(pipex->fd) == -1)
		handle_error_bonus(ERR_PIPE, pipex);
	pid = fork();
	if (pid == -1)
		handle_error_bonus(ERR_FORK, pipex);
	if (pid == 0)
	{
		close(pipex->fd[0]);
		open_infile(pipex);
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[1]);
		close_fds_bonus(pipex);
		execute(pipex);
	}
	else
	{
		close(pipex->fd[1]);
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	create_children(t_pip_bonus *pipex)
{
	int	pid;

	if (pipe(pipex->fd) == -1)
		handle_error_bonus(ERR_PIPE, pipex);
	pid = fork();
	if (pid == -1)
		handle_error_bonus(ERR_FORK, pipex);
	if (pid == 0)
	{
		close(pipex->fd[0]);
		dup2(pipex->fd[1], STDOUT_FILENO);
		close(pipex->fd[1]);
		close_fds_bonus(pipex);
		execute(pipex);
	}
	else
	{
		close(pipex->fd[1]);
		dup2(pipex->fd[0], STDIN_FILENO);
		close(pipex->fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	last_child(t_pip_bonus *pipex)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		handle_error_bonus(ERR_PIPE, pipex);
	if (pid == 0)
	{
		close(pipex->fd[1]);
		dup2(pipex->fd[0], STDIN_FILENO);
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->fd[0]);
		close_fds_bonus(pipex);
		execute(pipex);
	}
}

int	create_pipes(t_pip_bonus *pipex)
{
	int	status;
	int	i;

	i = 0;
	status = EXIT_SUCCESS;
	if (pipex->here_doc_flag)
		pipex->outfile_fd = open_file(pipex->argv[pipex->argc - 1]);
	else
		pipex->outfile_fd = open_file(pipex->argv[pipex->argc - 1]);
	first_child(pipex);
	
	while (i < pipex->num_pipes)
	{
		create_children(pipex);
		i++;
	}
	last_child(pipex);
	close_fds_bonus(pipex);
	return (status);
}
