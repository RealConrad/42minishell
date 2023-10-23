/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:28:03 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/20 18:03:55 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_env	*head;
	head = copy_env_to_linked_list(envp, head);
	env(head);
	free_env_linked_list(head);
	// executor(envp);

	// setup_signals();
	
	// env();
	// Mock shell to check if signal functions actually get called
	// while (1)
	// {
	// 	char *input = readline("minishell> ");
	// 	if (!input)
	// 	{
	// 		printf("Ctrl+D was pressed!\n");
	// 		free(input);
	// 		break;
	// 	}
	// 	if (input && input[0] != '\0' && input[0] != '\n')
	// 		add_history(input);
	// 	free(input);
	// }
	return (0);
}