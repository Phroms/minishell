/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/18 16:33:34 by agrimald         ###   ########.fr       */
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

t_tokens *init_token(t_env **env);
int add_words(t_tokens *tokens, char *str, size_t len, int type);
int special_char(char c);
void free_tokens(t_tokens *tokens);

/*void execute_command(CommandInfo *command)
{
    pid_t pid = fork(); // Crear un nuevo proceso

    if (pid == -1)
    {
        // Error en la creación del proceso hijo
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Este código se ejecuta en el proceso hijo
        if (execvp(command->args[0], command->args) == -1)
        {
            // Error en la ejecución del comando
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // Este código se ejecuta en el proceso padre
        int status;
        waitpid(pid, &status, 0); // Esperar a que el proceso hijo termine
    }
}

int main()
{
    char *input;
    t_tokens *tokens;
    t_env **env = NULL;

    while (1)
    {
        input = readline(" > ");
        if (!input)
            exit(0);
        if (input)
        {
            printf("Texto ingresado: %s\n", input);

            // Inicializar tokens
            tokens = init_token(env);

            // Parsear la entrada
            if (parser(tokens, input) == 42)
            {
                // Manejar el error
                printf("Error en la entrada.\n");
            }
            else
            {
                // Imprimir tokens (opcional)
                print_tokens(tokens);

                // Ejecutar comandos según los tokens
                size_t i = 0;
                while (i < tokens->size)
                {
                    t_word *current_word = &tokens->words[i];

                    // Verificar si el token es un comando ejecutable
                    if (current_word->type == 0)
                    {
                        CommandInfo command;
                        command.args = malloc(sizeof(char *) * 2); // Tamaño 2 para el comando y NULL al final
                        command.args[0] = current_word->word;
                        command.args[1] = NULL; // Termina la lista de argumentos

                        // Ejecutar el comando
                        execute_command(&command);

                        // Liberar memoria de los argumentos
                        free(command.args);
                    }

                    i += 1;
                }

                // Liberar memoria de tokens
                free_tokens_memory(tokens);
            }

            free(input);
        }
    }

    return 0;
}*/
int main()
{
	char *input;
	char *text;
	char *args[3];

	while (1)
	{
		input = readline(" > ");
		if (!input)
			exit(0);
		if (input)
		{
			printf("Texto ingresado: %s\n", input);
			t_tokens *tokens = init_token(NULL);
			if (add_words(tokens, input, strlen(input), 0))
			{
				if (tokens->size > 0)
				{
					printf("Palabra: %s\nTipo: %d\n", tokens->words[0].word, tokens->words[0].type);
					if (tokens->size == 1 && tokens->words[0].type == 0)
					{
						if (strcmp(tokens->words[0].word, "pwd") == 0)
						{
							pwd();
						}
						else if (strncmp(tokens->words[0].word, "echo ", 5) == 0)
						{
							text = input + 5;
							args[0] = "echo";
							args[1] = text;
							args[2] = NULL;
							echo(args);
						}
					}
				}
			}
			free_tokens(tokens);
			free(input);
		}
	}
	return (0);
}
