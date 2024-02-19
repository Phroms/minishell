/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:59:59 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/08 17:28:17 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_env *env, char	*str)
{
	int		i;
	char	*find;

	i = 0;
	while (env->env_cpy[i])
	{
		find = ft_strnstr(env->env_cpy[i], str, ft_strlen(str));
		if (find != NULL)
			return (find);
		i++;
	}
	return (NULL);
}

static int	exec_no_path(t_expander *exp)
{
	if (execve(exp->exp_matr[0], exp->exp_matr, NULL) == -1)
		return (1);
	return (0);
}

static int	command_execute(t_expander *exp, t_env *env)
{
	char	**paths;
	char	*cmd_path;
	int		i;
	int		comp;
	char	*all_path;

	i = 0;
	all_path = ft_getenv(env, "PATH=");
	if (access(exp->exp_matr[0], F_OK | X_OK) == 0)
		return (exec_no_path(exp));
	paths = ft_split(all_path, ':');
	while (paths[i])
	{
		cmd_path = ft_strjoin(ft_strjoin(paths[i], "/"), exp->exp_matr[0]);
		comp = execve(cmd_path, exp->exp_matr, NULL);
		free(cmd_path);
		if (comp == 0)
		{
			free(paths);
			return (0);
		}
		i++;
	}
	free(paths);
	return (1);
}

int	execute(t_expander *exp, t_executor *exec, t_env *env)
{
	if (command_done(exp, exec, env) == 0)
		return (0);
	else if (command_execute(exp, env) == 0)
		return (0);
	else
		ft_printf("%s: command not found :(\n", exp->exp_matr[0]);
	return (127);
}

void	child_process(t_expander *exp, t_executor *exec, t_env *env, int c)
{
	if (exec->err_flag)
		exit(1);
	signals();
	if (exec->num_pipes != 0 && c > 0)
	{
		close(exec->prev_pipe[OUT]);
		if (exec->redirection[IN] == 0)
			dup2(exec->prev_pipe[IN], STDIN_FILENO);
		close(exec->prev_pipe[IN]);
	}
	if (exec->num_pipes == 0 && exec->fd_output)
		dup2(exec->fd_output, STDOUT_FILENO);
	if (exec->num_pipes != 0)
	{
		close(exec->pipe_fd[IN]);
		if (exec->cmd_cont == exec->num_pipes && exec->fd_output)
			dup2(exec->fd_output, STDOUT_FILENO);
		else if (c == exec->num_pipes)
			dup2(exec->fd_init[OUT], STDOUT_FILENO);
		else
			dup2(exec->pipe_fd[OUT], STDOUT_FILENO);
		close(exec->pipe_fd[OUT]);
	}
	exit(execute(exp, exec, env));
}
// 127 para comandos