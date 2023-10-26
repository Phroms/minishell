/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:30:15 by agrimald          #+#    #+#             */
/*   Updated: 2023/10/26 19:10:31 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
/*void	lexer()
{
	
	 * Vas a guardar en una estructura el tipoo de textoo que te han pasa
	 * ej:   echo   hola   >   file.txt   |     ls      -la    <<   file_hrdc a | 
	 *       texto  texto  rd    texto    pipe  texto  texto   rd     texto
	 *
	 * RD -> << = HD  |  < = inFile  |  >> = append  |  > = outFile
	 * 
}*/


/*int	main(int ac, char **av, char **env)
{
	while (1)
	{
		 * Estudiar que es la libreria READLINE
		char *str;
		 * Guardar la linea leida en la str
		lexer(str);
	}
}*/

int main(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	char	*input;

	printf("➜ ");
	while ((input = readline("")) != NULL)
	{
		if (input[0] == '\0')
		{
			free(input);
			break;
		}
		printf("\nEntrada: %s\n", input);
		free(input);
		printf("➜ ");
	}
	return (0);
}
