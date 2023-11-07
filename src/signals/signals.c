/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:21:33 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/07 17:52:13 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//#include <signal.h>
//#include <readline/readline.h>
//#include <readline/history.h>
//#include <stdio.h>
//#include <stdlib.h>

void	signal_ctrlC(int sig)
{
	if (sig == SIGINT) //esto le indica que interrumpe el programa;
	{
		printf("\n");
		rl_on_new_line(); // esto indica que el cursor debe moverse a una nueva linea;
		rl_replace_line("", 0); // reemplaza el antiguo texto con uno nuevo
		rl_redisplay(); // muestra lo escrito por la funcion anterior.
	}
}

void	signal_ctrlD(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrlC);
}

int	main()
{
	signal_ctrlD();
	signal_ctrlC(SIGINT);

	char *input;
	while (1)
	{
		input = readline("Ingrese el texto: ");
		if (input)
		{
			printf("Texto ingresado: %s\n", input);
            free(input);
		}
	}
	return (0);
}
