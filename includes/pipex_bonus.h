/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:01:50 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/10/20 14:07:44 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* -------------------------------- Includes -------------------------------- */

# include "common.h"

/* -------------------------------- Typedefs -------------------------------- */

typedef struct s_pip_bonus
{
	bool	here_doc_flag;
	int		argc;
	int		fd[2];
	int		hdfd[2];
	int		infile_fd;
	int		outfile_fd;
	int		last_pid;
	int		num_pipes;
	char	path[PATH_MAX];
	char	*tmp;
	char	**envp_path;
	char	**argv;
	char	**envp;
	char	**cmd_split;
}	t_pip_bonus;

/* ------------------------- Error Handler functions ------------------------ */

void	handle_error_bonus(t_errors err, t_pip_bonus *pipex);
void	error_bonus(t_errors err, char *cmd_or_file, t_pip_bonus *pipex);

/* ---------------------------------- Utils --------------------------------- */
void	init(t_pip_bonus *pipex, int ac, char **av, char **ep);
void	free_bonus(t_pip_bonus *pipex);
void	get_envp_path(t_pip_bonus *pipex);
int		open_file(char *file);
void	close_fds_bonus(t_pip_bonus *pipex);
char	*strjoin_pipex(char *s1, char *s2);
char	*find_cmd_path(t_pip_bonus *pipex, char *cmd);

/* -------------------- Multipe pipe handle function ---------------------- */

void	execute(t_pip_bonus *pipex);
int		create_pipes(t_pip_bonus *pipex);

#endif