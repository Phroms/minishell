/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:52:55 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/08 17:06:53 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	more_redirections(t_expander *exp, char c)
{
	t_expander	*node;

	node = exp->next;
	while (node)
	{
		if (node->token[0] == c)
			return (1);
		node = node->next;
	}
	return (0);
}

//Va entrant amb el while i quan ja es la ultima redireccio entra
//i fa l'open
int	redirect_input(char *filename, t_executor *exec, t_expander *exp)
{
	int	fd;

	if (!filename)
		return (1);
	if (!more_redirections(exp, '<') && exec->redirection[IN] == 0)
	{
		fd = open (filename, O_RDONLY);
		if (fd < 0)
		{
			perror("Error al abrir el archivo de entrada :(\n");
			exec->ret_val = 1;
			return (1);
		}
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("Error al redirigir :(\n");
			close(fd);
			return (1);
		}
		close(fd);
		exec->redirection[IN] = 1;
	}
	return (0);
}

static int	only_open(char *filename, t_expander *exp)
{
	int	fd;

	fd = -1;
	if (exp->exp_type == OUTP || exp->exp_type == OUTP_FD)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (exp->exp_type == APPEND || exp->exp_type == APPEND_FD)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		perror("Error al abrir archivo de salida :(\n");
		return (1);
	}
	close (fd);
	return (0);
}

int	redirect_output(char *filename, t_expander *exp, t_executor *exec, int fd)
{
	if (!more_redirections(exp, '>') && exec->redirection[OUT] == 0)
	{
		if (exp->exp_type == OUTP || exp->exp_type == OUTP_FD)
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (exp->exp_type == APPEND || exp->exp_type == APPEND_FD)
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd < 0)
		{
			perror("Error al abrir archivo de salida :(\n");
			return (1);
		}
		exec->fd_output = fd;
		exec->redirection[OUT] = 1;
	}
	else
		if (only_open(filename, exp))
			return (1);
	return (0);
}

int	redirect_heredoc(int fd, t_executor *exec)
{
	(void)fd;
	exec->redirection[IN] = 1;
	return (0);
}
