/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:35:11 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/28 12:24:59 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_minishell(t_minishell *minishell);
static void	parse_and_execute(t_lexer **lexer, t_minishell *minishell);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Run as ./minishell with no args\n", 2);
		exit(EXIT_FAILURE);
	}
	minishell = (t_minishell){};
	minishell.exit_code = get_exit_code();
	copy_std_fds(&minishell);
	copy_env_variables(&minishell.head_env, envp);
	run_minishell(&minishell);
	free_env_linked_list(minishell.head_env);
	return (0);
}

static void	run_minishell(t_minishell *minishell)
{
	char		*input;
	t_lexer		*lexer;

	while (1)
	{
		setup_signals();
		input = readline("minishell> ");
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (input && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		lexer = tokenise(input);
		parse_and_execute(&lexer, minishell);
		free(input);
		reset_fds(minishell);
	}
}

static void	parse_and_execute(t_lexer **lexer, t_minishell *minishell)
{
	if (parser(lexer, minishell) == SUCCESS)
	{
		executor(minishell);
		free_cmd_table(minishell->cmd_table);
	}
	else
	{
		set_exit_code(2);
		free_lexer(lexer);
	}
}
