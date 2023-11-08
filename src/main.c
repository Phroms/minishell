
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

int	main()
{
	signal_ctrl_c(SIGINT);
	signal_ctrl_d();

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
