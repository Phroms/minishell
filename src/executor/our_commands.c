/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:49:49 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/12 17:02:04 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	our_cmd(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		command[i] = ft_tolower(command[i]);
		i++;
	}
	if (!ft_strcmp(command, "echo"))
		return (0);
	else if (!ft_strcmp(command, "cd"))
		return (0);
	else if (!ft_strcmp(command, "pwd"))
		return (0);
	else if (!ft_strcmp(command, "export"))
		return (0);
	else if (!ft_strcmp(command, "unset"))
		return (0);
	else if (!ft_strcmp(command, "env"))
		return (0);
	else if (!ft_strcmp(command, "exit"))
		return (0);
	return (1);
}

static void	pass_tolower(t_expander *exp)
{
	int	i;

	i = 0;
	while (exp->exp_matr[0][i] != '\0')
	{
		ft_tolower(exp->exp_matr[0][i]);
		i++;
	}
}

/****  FALTA RELLENAR LAS FUNCIONES CON SUS PARAMETROS  ****/
int	command_done(t_expander *exp, t_executor *exec, t_env *env)
{
	exec->redirection[IN] = 0;
	exec->redirection[OUT] = 0;
	pass_tolower(exp);
	if (exec->num_pipes == 0 && exec->fd_output)
		dup2(exec->fd_output, STDOUT_FILENO);
	if (!ft_strcmp(exp->exp_matr[0], "echo"))
		return (ft_echo((char **)exp->exp_matr));
	if (!ft_strcmp(exp->exp_matr[0], "cd"))
	{
		if (exp->len == 2 && exp->exp_matr[1] && exp->exp_matr[1][0] == '\0')
			return (0);
		return (ft_cd(exp->exp_matr, exp->len, env));
	}
	else if (!ft_strcmp(exp->exp_matr[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(exp->exp_matr[0], "export"))
		return (ft_export(&exp->exp_matr[1], env));
	else if (!ft_strcmp(exp->exp_matr[0], "unset"))
		return (ft_unset(exp->exp_matr[1], env));
	else if (!ft_strcmp(exp->exp_matr[0], "env"))
		return (ft_env(env));
	else if (!ft_strcmp(exp->exp_matr[0], "exit"))
		return (ft_exit(exp->exp_matr, exp->len));
	return (127);
}
