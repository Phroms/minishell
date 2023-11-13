/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/13 19:25:10 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	main()
{
	char	*input;
	while (1)
	{
		input = readline("Ingrese el texto: ");
		if (input)
		{
			printf("Texto leido perfectamente: %s\n", input);
			free(input);
		}
	}
	return (0);
}*/

int	main()
{
	signals();

	char	*input;
	char	*text;
	char	*args[3];

	while (1)
	{
		input = readline(" > ");
		if (!input)
			exit(0);
		if (input)
		{
			printf("Texto ingresado: %s\n", input);
			if (ft_strcmp(input, "pwd") == 0)
			{
				pwd();
			}
			else if (ft_strncmp(input, "echo ", 5) == 0)
			{
				text = input + 5;
				args[0] = "echo";
				args[1] = text;
				args[2] = NULL;
				echo(args);
			}
            free(input);
		}
	}
	return (0);
}
