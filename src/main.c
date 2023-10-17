/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkumbhan <hkumbhan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:28:03 by cwenz             #+#    #+#             */
/*   Updated: 2023/10/17 09:12:39 by hkumbhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline(NULL);
		if (str == NULL)
			break ;
		add_history(str);
		// do something
		free(str);
	}
	return (EXIT_SUCCESS);
}
