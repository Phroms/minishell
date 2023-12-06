/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/29 18:54:00 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void	execute_command(CommandInfo *command, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(command->args[0], command->args, env) == -1)
		{
			perror("execve");
			printf("Error ejecutando el comando: %s\n", command->args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;

	signals();
	while (1)
	{
		input = readline(" > ");
		if (!input)
			exit(0);
		if (input)
		{
			printf("Texto ingresado: %s\n", input);
			// Inicializar tokens
			t_tokens	*tokens = init_token(NULL);
			// Parsear la entrada
			if (check_input(input))
			{
				// Error en la entrada
				printf("Error en la entrada.\n");
			} else {
				size_t i = 0;
				while (i < ft_strlen(input))
				{
					if (is_space(tokens, input + i)) {
						// Manejar espacios
						i += is_space(tokens, input + i);
					} else if (is_rd(input[i])) {
						// Manejar redirecciones
						// ...
					} else if (is_marks(tokens, input + i)) {
						// Manejar comillas
						i += is_marks(tokens, input + i);
					} else {
						i += string_tokens(tokens, input + i);
					}
					if (tokens->error == 1)
						break ;
				}
				if (!tokens->error)
				{
					// Ejecutar comandos según los tokens
					size_t j = 0;
					while (j < tokens->size)
					{
						t_word *current_word = &tokens->words[j];

						// Verificar si el token es un comando ejecutable
						if (current_word->type == 0) {
							// Obtener el nombre del comando
							char *command_name = current_word->word;
							// Ejecutar comandos específicos
							if (strcmp(command_name, "echo") == 0)
								echo(tokens->env);
							else if (strcmp(command_name, "pwd") == 0)
								pwd();
							else if (strcmp(command_name, "env") == 0)
								// Agregar lógica para el comando env
								// ...
							else
							{
								// Otros comandos
								printf("Comando desconocido: %s\n", command_name);
							}
						}
						j += 1;
					}
				}
			}
			// Liberar memoria de tokens
			free_tokens(tokens);
			free(input);
		}
	}
	return (0);
}*/

void	ft_env(char *input, char *env[])
{
	int i;

	i = 0;
	if (input[0] == 'e' && input[1] == 'n' && input[2] == 'v' && input[3] == '\0')
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}

int	main(int argc, char *argv[], char *env[])
{
    (void)argc;
    (void)argv;
	char		*input;
	t_tokens	*tokens = NULL;
	//t_expander	*exp;
	int			err;

	signals();
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(0);
		ft_env(input, env);
		err = parser(tokens, input, env);
		// hacer una o mas funciones que haga los comandos(cmd);
		//exp = expander(tokens);
		//executor();
	}
	//free_all();
    return (0);
}

/* funcion que vera si hara comandos */
/*void	is_command(char *str, char *cmd)
{
	if (ft_strcmp(cmd, "pwd"))
		hacer mi comando pwd;
	if (ft_strcmp(cmd, "echo"))
		hacer mi comando echo;
	if (ft_strcmp(cmd, "cd"))
		hacer mi comando cd;
	podemos hacer un ft_strcmp(str, cmd)
}*/