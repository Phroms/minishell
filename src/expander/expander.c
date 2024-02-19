/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:12:30 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/07 16:58:30 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expander	*expander(t_tokens *tokens, t_env *env, t_executor *exec)
{
	t_expander	*exp;

	exp = malloc(sizeof(t_expander));
	if (!exp)
	{
		perror("Error al asignar memoria para un nodo");
		exit(EXIT_FAILURE);
	}
	exp->prev = NULL;
	exp->next = NULL;
	exp_expand_var(tokens, env, exec);
	exp->num_pipes = count_pipes(tokens);
	exp_split_to_expand(tokens, &exp);
	return (exp);
}
