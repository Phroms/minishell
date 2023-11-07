/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:42:36 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/07 17:50:30 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>*/

int	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*s++)
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (*s1 != '\0' || *s2 != '\0'))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}

int	echo(char **args)
{
	bool	print_line;

	print_line = true;
	if (ft_strncmp(*args, "echo", ft_strlen(*args)) != 0)
		return (EXIT_FAILURE);
	args++;
	if (*args && ft_strncmp(*args, "-n", ft_strlen("-n") + 1) == 0)
	{
		print_line = false;
		args++;
	}
	while (*args != NULL)
	{
		if (printf("%s", *args) != ft_strlen(*args))
			return (EXIT_FAILURE);
		if (ft_strlen(*args) != 0 && *(args + 1) != NULL)
			if (printf(" ") != ft_strlen(" "))
				return (EXIT_FAILURE);
		args++;
	}
	if (print_line)
		if (printf("\n") != ft_strlen("\n"))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	(void)argc;
	return echo(argv + 1);
}

	/*	TEST MANUAL */

/*
bash-3.2$ echo hola
hola ✅
bash-3.2$ echo -n hola
holabash-3.2$ ❌
bash-3.2$ echo -n-n hola
-n-n hola ✅
bash-3.2$ echo -----n hola
-----n hola ✅
bash-3.2$ echo -nnnnnn hola
holabash-3.2$ ❌
bash-3.2$ echo nnnnn hola
nnnnn hola ✅
bash-3.2$
*/
