/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:50:44 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/07 15:59:23 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_a_num(char num)
{
	if (num >= '0' && num <= '9')
		return (0);
	return (1);
}

static int	check_num(char **argv)
{
	char	*num;
	int		i;

	num = argv[1];
	i = 0;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i])
	{
		if (is_a_num(num[i]))
		{
			printf("exit: %s: numeric argument required\n", num);
			return (255);
		}
		i++;
	}
	return (ft_atoi(num));
}

int	ft_exit(char **argv, int len)
{
	int	ex;

	ex = 0;
	if (len == 1)
		exit (0);
	if (len > 2)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	ex = check_num(argv);
	printf("exit\n");
	exit(ex);
}
