/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/09 14:39:11 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space_main(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	init_minishell(t_tokens	*t, t_executor *exec, t_env *e)
{
	int			err;
	char		*input;
	t_expander	*exp;

	signals();
	while (1)
	{
		input = readline("minishell-> ");
		if (!input)
			exit(1);
		if (input[0] != '\0' && is_space_main(input))
		{
			err = parser(&t, input, e->env_cpy);
			exp = expander(t, e, exec);
			if (err == 0)
			{
				if (exp->exp_matr[0])
					err = executor(exp, e, t, exec);
				destroy_all(&t, &exp);
			}
			free(input);
		}
		else
			free(input);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_tokens	*tokens;
	t_executor	exec;
	t_env		*e;

	(void)argc;
	(void)argv;
	tokens = NULL;
	e = malloc(sizeof(t_env));
	e->env_cpy = env;
	exec.env = e;
	exec.ret_val = 0;
	init_minishell(tokens, &exec, e);
}
