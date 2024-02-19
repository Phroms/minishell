/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:08:43 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/08 19:49:12 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp_hd(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	bucle_heredoc(int fd, char *str)
{
	char	*line;

	signals();
	while (42)
	{
		line = readline("heredoc > ");
		if (ft_strcmp_hd(line, str) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 2);
		free(line);
	}
}

static int	init_heredoc(t_expander *exp, char *str)
{
	int		fd[2];

	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	else
		bucle_heredoc(fd[OUT], str);
	close(fd[OUT]);
	dup2(fd[IN], STDIN_FILENO);
	close(fd[IN]);
	exp->heredoc_fd = fd[IN];
	return (0);
}

int	heredoc(t_expander *exp)
{
	t_expander	*node;

	node = exp;
	while (node != NULL)
	{
		if (node->exp_type == HEREDOC || node->exp_type == HEREDOC_PIPE)
		{
			if (init_heredoc(node, node->next->exp_matr[0]))
				return (1);
		}
		node = node->next;
	}
	return (0);
}
