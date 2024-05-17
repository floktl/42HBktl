/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:49:29 by fkeitel           #+#    #+#             */
/*   Updated: 2024/05/17 14:48:14 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_env_list(t_env **env_list)
{
	t_env	*current;
	t_env	*next;

	if (!env_list || !(*env_list))
		return ;
	current = *env_list;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		current->name = NULL;
		free(current->value);
		current->value = NULL;
		free(current);
		current = next;
	}
	*env_list = NULL;
	free(env_list);
	env_list = NULL;
}

//	function to free the entire parsing tree
void	free_tree(t_tree *parse_tree, int env)
{
	if (!parse_tree)
		return ;
	if (parse_tree->cmd_brch)
	{
		free(parse_tree->cmd_brch);
		parse_tree->cmd_brch = NULL;
	}
	if (parse_tree->args_num)
	{
		free_two_dimensional_array(parse_tree->arguments);
	}
	if (env == 1 && parse_tree->env)
	{
		free_env_list(parse_tree->env);
		parse_tree->env = NULL;
	}
	if (parse_tree->child_pipe)
		free_tree(parse_tree->child_pipe, 0);
	free(parse_tree);
	parse_tree = NULL;
}

//	function to free an two dimensional array
void	ft_free(char **split, int words)
{
	while (words > 0)
	{
		if (split[words - 1])
			free(split[words - 1]);
		words--;
	}
	free(split);
}
