/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:40:04 by harsh             #+#    #+#             */
/*   Updated: 2023/10/20 13:51:30 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd_path(t_pip_bonus *pipex, char *cmd)
{
	int		j;
	char	*cmd_path;

	cmd_path = strjoin_pipex(cmd, "");
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	cmd_path = NULL;
	j = -1;
	while (pipex->envp_path[++j] != NULL)
	{
		pipex->tmp = strjoin_pipex(pipex->envp_path[j], "/");
		if (pipex->tmp == NULL)
			handle_error_bonus(ERR_MEMORY, pipex);
		cmd_path = strjoin_pipex(pipex->tmp, cmd);
		if (cmd_path == NULL)
			handle_error_bonus(ERR_MEMORY, pipex);
		free(pipex->tmp);
		pipex->tmp = NULL;
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	pipex->tmp = NULL;
	return (NULL);
}

void	execute(t_pip_bonus *pipex)
{
	char	*path;

	path = find_cmd_path(pipex, pipex->argv[0]);
	if (path == NULL)
	{
		error_bonus(ERR_CMD, pipex->argv[0], pipex);
		free_arr(pipex->argv);
		exit(EXIT_FAILURE);
	}
	if (execve(path, pipex->argv, pipex->envp) == -1)
	{
		free(path);
		error_bonus(ERR_CMD, pipex->argv[0], pipex);
		free_arr(pipex->argv);
		exit(EXIT_FAILURE);
	}
	return ;
}
