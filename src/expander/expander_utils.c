/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:08:24 by hkumbhan          #+#    #+#             */
/*   Updated: 2023/11/27 14:13:37 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks if the varaible name is valid
/// @param c first character after $
/// @return True if the char after $ is alphabet or '_'
int	check_var(char c)
{
	if (ft_isalnum(c) == TRUE || c == '_')
		return (TRUE);
	return (FALSE);
}

/// @brief Exapnds the value of $?
/// @param ret address of the return string
/// @param minishell 
/// @return returns 2 since $? is length of 2
int	special_var(char **ret, t_minishell *minishell)
{
	char	*tmp;

	tmp = ft_itoa(*minishell->exit_code);
	*ret = ft_strjoin_gnl(*ret, tmp);
	free(tmp);
	return (2);
}

/// @brief Expands speacil chacrter other than ? after $
/// @param ret address of the return string
/// @param str string from lexer
/// @return returns 2
int	special_char(char **ret, char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strndup(str, 2);
	*ret = ft_strjoin_gnl(*ret, tmp);
	free(tmp);
	return (2);
}

int	check_expansion(char *str, int i, t_token tok)
{
	if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '\"')
		&& tok == WORD)
		return (FALSE);
	if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '\"')
		&& tok == DQUOTE)
		return (TRUE);
	return (-1);
}
