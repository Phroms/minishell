/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:42:36 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/12 16:31:25 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_new(char *old, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old[i])
	{
		if (old[i] != '\'')
		{
			new[j] = old[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*quit_comillas(char *str)
{
	int		len;
	char	*new;

	len = ft_strlen(str);
	if (str[0] == '\'')
	{
		new = malloc((len - 1) * sizeof(char));
		new = fill_new(str, new);
		free(str);
		return (new);
	}
	return (str);
}

int	ft_echo(char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		argv[i] = quit_comillas(argv[i]);
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
