/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:52:29 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/09 14:44:43 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mod_strcmp(char *cmd, char *env)
{
	int	i;

	i = 0;
	while (cmd[i] && env[i])
	{
		if (cmd[i] == '=' && env[i] == '=')
			return (TRUE);
		if (cmd[i] != env[i])
			return (FALSE);
		i++;
	}
	if (cmd[i] == '\0' && (env[i] == '\0' || env[i] == '='))
		return (TRUE);
	return (FALSE);
}

int	check_env_without_value(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	replace_value(char *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (env->env_cpy[i] != NULL)
	{
		if (mod_strcmp(cmd, env->env_cpy[i]) == TRUE)
		{
			free(env->env_cpy[i]);
			env->env_cpy[i] = ft_strdup(cmd);
			return ;
		}
		i++;
	}
	normal_export(cmd, env);
}

int	var_exist(char *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (env->env_cpy[i] != NULL)
	{
		if (mod_strcmp(cmd, env->env_cpy[i]) == TRUE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	bubble_sort(char **arr, int size, int i)
{
	char	*temp;

	if (i == size - 1)
		return ;
	if (ft_strcmp(arr[i], arr[i + 1]) > 0)
	{
		temp = arr[i];
		arr[i] = arr[i + 1];
		arr[i + 1] = temp;
	}
	bubble_sort(arr, size, i + 1);
}
