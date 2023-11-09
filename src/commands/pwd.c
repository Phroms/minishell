/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:20:28 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/09 21:00:54 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/minishell.c"
#include "minishell.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}

/*int main(int argc, char **argv)
{
	(void)argv;
	if (argc == 2)
		pwd();
	return (0);
}*/
