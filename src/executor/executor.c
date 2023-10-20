/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:50:36 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/20 14:26:04 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	handle_builtin(t_pip_bonus *pipex);
static void	handle_cmd(t_pip_bonus *pipex);

/*
	1. Create child process for everything besides builtins
	2. 
*/

void	executor(char **env)
{
	char 		*cmds[] = {"ls", "-la", NULL};
	bool		is_builtin_only = false;
	t_pip_bonus	*pipex;

	pipex = (t_pip_bonus *)ft_callofc(1, sizeof(t_pip_bonus));

	init(pipex, 2, cmds, env);
	pipex->num_pipes = 0;
	if (is_builtin_only)
		handle_builtin(pipex);
	else
		handle_cmd(pipex);
}

static void	handle_cmd(t_pip_bonus *pipex)
{
	int	status;

	if (pipex->here_doc_flag)
		pipex->outfile_fd = open_file(pipex->argv[pipex->argc - 1]);
	else
		pipex->outfile_fd = open_file(pipex->argv[pipex->argc - 1]);
	status = create_pipes(pipex);
	if (status != EXIT_SUCCESS)
		perror("Error when creating pipes!\n");
}

static void	handle_builtin(t_pip_bonus *pipex)
{
	if (ft_strncmp(pipex->argv[0], "echo", 4))
		echo(pipex->argv[1]);
	else if (ft_strncmp(pipex->argv[0], "cd", 2))
		cd(pipex->argv[1]);
	else if (ft_strncmp(pipex->argv[0], "pwd", 3))
		pwd();
	else if (ft_strncmp(pipex->argv[0], "env", 3))
		env(pipex->envp);
	else
		perror("Invalid built in command found!\n");
}