/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:42:36 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/23 21:36:54 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("%s", *args);
		args++;
		if (*args != NULL)
			printf(" ");
	}
	if (print_line)
		printf("\n");
	return (EXIT_SUCCESS);
}

/*int	main(int argc, char **argv)
{
	(void)argc;
	return echo(argv + 1);
}*/

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
