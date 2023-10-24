#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	// executor(envp);
	t_lexer	*lexer;

	setup_signals();
	// Mock shell to check if signal functions actually get called
	while (1)
	{
		char *input = readline("minishell> ");
		if (!input)
		{
			printf("Ctrl+D was pressed!\n");
			print_list(&lexer);
			lst_del(&lexer);
			free(input);
			break;
		}
		lexer = tokenise(input);
		if (lexer == NULL)
		{
			printf("Invalid input\n");
			//continue ;
		}
		if (input && input[0] != '\0' && input[0] != '\n')
			add_history(input);
		print_list(&lexer);
		lst_del(&lexer);
		free(input);
	}
				
	//lexer = tokenise("ls>filename");
	//if (lexer != NULL)
	//{
	//	print_list(&lexer);
	//	lst_del(&lexer);
	//}
	return (0);
}
