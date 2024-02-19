/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:52:19 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/10 19:32:28 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_special_export(t_env *env, int count, int i)
{
	if (i < count)
	{
		printf("declare -x %s\n", env->env_cpy[i]);
		print_special_export(env, count, i + 1);
	}
}

void	special_export(t_env *env)
{
	char	*equal_sign;
	int		i;

	i = 0;
	while (env->env_cpy[i] != NULL)
	{
		equal_sign = ft_strchr(env->env_cpy[i], '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", env->env_cpy[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
			printf("declare -x %s\n", env->env_cpy[i]);
		i++;
	}
}

void	normal_export(char *cmd, t_env *env)
{
	char	**patata;
	int		i;
	int		j;

	i = 0;
	patata = env->env_cpy;
	while (patata[i] != NULL)
		i++;
	env->env_cpy = ft_calloc(sizeof(char *), i + 2);
	j = 0;
	while (j < i)
	{
		env->env_cpy[j] = ft_strdup(patata[j]);
		j++;
	}
	env->env_cpy[j++] = ft_strdup(cmd);
	env->env_cpy[j] = NULL;
	if (ft_strstr(cmd, "PATH=") == cmd)
		handle_path_export(cmd, env);
}

int	ft_export(char **cmd, t_env *env)
{
	if (cmd[0] == NULL)
	{
		special_export(env);
		return (0);
	}
	else
		return (handle_export_commands(cmd, env));
}

int	handle_export_commands(char **cmd, t_env *env)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i], "0") == 0)
		{
			printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
			return (1);
		}
		if (mod_strcmp(cmd[i], "PATH="))
			normal_export(cmd[i], env);
		else
		{
			if (var_exist(cmd[i], env) == TRUE)
				replace_value(cmd[i], env);
			else
				normal_export(cmd[i], env);
		}
		i++;
	}
	return (0);
}
