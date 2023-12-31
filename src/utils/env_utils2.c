/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:14:58 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 17:22:23 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env_linked_list(t_env **array, int count);
static void	assign_array(t_env *head, t_env **array);

/// @brief Prints the env linked list in ascending order and with the export
/// format.
/// @param head The head node of the env linked list.
void	print_env_ascending(t_env *head)
{
	t_env	**array;
	int		i;
	int		count;

	i = 0;
	count = count_env_variables(head);
	array = (t_env **)ft_calloc(count, sizeof(t_env *));
	if (!array)
		return ;
	assign_array(head, array);
	sort_env_linked_list(array, count);
	while (array[i])
	{
		ft_fprintf(STDOUT_FILENO, "declare -x %s\n", array[i]->full_string);
		i++;
	}
	free(array);
}

/// @brief Counts the number of env variables stored in the linked list
/// @param head A pointer to the first node in the linked list
/// @return The amount of env variables stored in the linked list.
int	count_env_variables(t_env *head)
{
	int		i;
	t_env	*temp;

	temp = head;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

/// @brief Sorts the given linked list in by ascii values
/// @param array The array to sort
/// @param count The length of the array
static void	sort_env_linked_list(t_env **array, int count)
{
	t_env	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/// @brief Converts the given env linked list into an array
/// @param head The head pointer
/// @param array The array to assign data to
static void	assign_array(t_env *head, t_env **array)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = head;
	while (temp)
	{
		array[i] = temp;
		temp = temp->next;
		i++;
	}
}

/// @brief Copies the env linked list into a `char** array`
/// @param head The head pointer to the env linked list
/// @return The `char** array`or NULL if failed.
char	**copy_env(t_env *head)
{
	int		i;
	char	**env;
	t_env	*temp;

	i = count_env_variables(head);
	temp = head;
	env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (temp)
	{
		env[i] = ft_strdup(temp->full_string);
		i++;
		temp = temp->next;
	}
	env[i] = NULL;
	return (env);
}
