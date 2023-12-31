/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwenz <cwenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:11:13 by cwenz             #+#    #+#             */
/*   Updated: 2023/11/25 17:22:13 by cwenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Adds a new node to the env variable linked list
int	add_env_node(t_env **head, char *key, char *full_string, char *value)
{
	t_env	*temp;
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->key = key;
	new_node->full_string = full_string;
	new_node->value = value;
	new_node->next = NULL;
	if (!(*head))
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
	return (EXIT_SUCCESS);
}

/// @brief Finds the node which holds the given key.
/// @param head A pointer to the first head of the env array
/// @param key The key to search for.
/// @return The node which holds the given key, else NULL if not found
t_env	*find_env_key(t_env *head, char *key)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		if (strcmp(temp->key, key) == EXIT_SUCCESS)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/// @brief Copes the given `envp` into a linked list format
/// @param head A pointer to which the data will be added
/// @param envp The array which will be used to create the linked list.
void	copy_env_variables(t_env **head, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		process_string(head, envp[i]);
		i++;
	}
}
