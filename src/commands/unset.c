/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:52:41 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/10 19:41:29 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char *variable, t_env *env)
{
	char	**env_ptr;
	int		i;

	i = 0;
	env_ptr = env->env_cpy;
	if (variable == NULL)
		return (0);
	while (env_ptr[i] != NULL)
	{
		if (ft_strncmp(env_ptr[i], variable, ft_strlen(variable)) == 0)
		{
			free(env_ptr[i]);
			while (env_ptr[i] != NULL)
			{
				env_ptr[i] = env_ptr[i + 1];
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
