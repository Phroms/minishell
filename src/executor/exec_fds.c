/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:48:23 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/07 16:53:41 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_command(t_executor *exec)
{
	dup2(exec->fd_init[IN], STDIN_FILENO);
	dup2(exec->fd_init[OUT], STDOUT_FILENO);
	close(exec->fd_init[IN]);
	close(exec->fd_init[OUT]);
}

void	init_fd(t_executor *exec)
{
	exec->pipe_fd[IN] = -1;
	exec->pipe_fd[OUT] = -1;
	exec->prev_pipe[IN] = -1;
	exec->prev_pipe[OUT] = -1;
	exec->fd_init[IN] = dup(STDIN_FILENO);
	exec->fd_init[OUT] = dup(STDOUT_FILENO);
	exec->redirection[IN] = 0;
	exec->redirection[OUT] = 0;
}
