/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2023/12/04 21:39:18 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*int main(int argc, char **argv, char **env)
{
    signals();
    char *input;
	(void)argc;
	(void)argv;
    while (1)
    {
        input = readline(" > ");
        if (!input)
            exit(0);
        if (input)
        {
            printf("Texto ingresado: %s\n", input);
            t_tokens *tokens = init_token(NULL);
            if (parser(tokens, input) == 42)
            {
                printf("Error en la entrada.\n");
            }
            else
            {
                print_tokens(tokens);
                size_t i = 0;
                while (i < tokens->size)
                {
                    t_word *current_word = &tokens->words[i];
                    if (current_word->type == 0)
                    {
                        CommandInfo command;
                        command.args = malloc(sizeof(char *) * 2);
                        command.args[0] = current_word->word;
                        command.args[1] = NULL;
                        execute_command(&command, env);
                        free(command.args);
                    }
                    i += 1;
                }
            }
            free_tokens(tokens);
            free(input);
        }
    }
    return 0;
}*/

/*t_tokens *init_token(t_env **env);
int add_words(t_tokens *tokens, char *str, size_t len, int type);
int special_char(char c);
void free_tokens(t_tokens *tokens);*/

/* este parece que si */
void execute_command(CommandInfo *command, char **env)
{
    pid_t pid = fork();
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
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char **argv, char **env)
{
    signals();
	(void)argc;
	(void)argv;
    char *input;

    while (1) {
        input = readline(" > ");
        if (!input)
            exit(0);

        if (input) {
            printf("Texto ingresado: %s\n", input);

            // Inicializar tokens
            t_tokens *tokens = init_token(NULL);

            // Parsear la entrada
            if (parser(tokens, input) == 42) {
                // Manejar el error
                fprintf(stderr, "Error en la entrada.\n");
            } else {
                // Imprimir tokens (opcional)
                print_tokens(tokens);

                // Ejecutar comandos según los tokens
                size_t i = 0;
                while (i < tokens->size) {
                    t_word *current_word = &tokens->words[i];

                    // Verificar si el token es un comando ejecutable
                    if (current_word->type == 0) {
                        CommandInfo command;
                        command.args = malloc(sizeof(char *) * 2);
                        command.args[0] = current_word->word;
                        command.args[1] = NULL; // Termina la lista de argumentos

                        // Ejecutar el comando utilizando la función execute_command
                        execute_command(&command, env);

                        // Liberar memoria de los argumentos
                        free(command.args);
                    }

                    i += 1;
                }
            }

            // Liberar memoria de tokens
            free_tokens(tokens);
            free(input);
        }
    }

    return 0;
}

/*int main()
{
	signals();

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
						if (ft_strcmp(tokens->words[0].word, "pwd") == 0)
						{
							pwd();
						}
						else if (ft_strncmp(tokens->words[0].word, "echo ", 5) == 0)
						{
							text = input + 5;
							args[0] = "echo";
							args[1] = text;
							args[2] = NULL;
							echo(args);
						}
						else if (ft_strncmp(tokens->words[0].word, "env", 3) == 0)
						{
							env(args);
						}

					}
				}
			}
			free_tokens(tokens);
			free(input);
		}
	}
	return (0);
}*/

/*int main() {
    signals();

    char *input;

    while (1) {
        input = readline(" > ");
        if (!input)
            exit(0);

        if (input) {
            printf("Texto ingresado: %s\n", input);

            // Inicializar tokens
            t_tokens *tokens = init_token(NULL);

            // Parsear la entrada
            if (check_input(input)) {
                // Error en la entrada
                printf("Error en la entrada.\n");
            } else {
                size_t i = 0;
                while (i < strlen(input)) {
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
                        break;
                }

                if (!tokens->error) {
                    // Ejecutar comandos según los tokens
                    size_t j = 0;
                    while (j < tokens->size) {
                        t_word *current_word = &tokens->words[j];

                        // Verificar si el token es un comando ejecutable
                        if (current_word->type == 0) {
                            // Obtener el nombre del comando
                            char *command_name = current_word->word;

                            // Ejecutar comandos específicos
                            if (strcmp(command_name, "echo") == 0) {
                                echo(tokens->env);
                            } else if (strcmp(command_name, "pwd") == 0) {
                                pwd();
                            } else if (strcmp(command_name, "env") == 0) {
                                // Agregar lógica para el comando env
                                // ...
                            } else {
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

    return 0;
}*/

//este parece que no
/*void execute_env(char **env) 
{
    int i = 0;
    while (env[i] != NULL) 
	{
        printf("%s\n", env[i]);
        i++;
    }
}

int main(int argc, char **argv, char **env)
{
	signals();
    (void)argc;
    (void)argv;

    char *input_buffer = NULL;
    size_t buffer_size = 0;

    while (1)
    {
        printf("> ");
        getline(&input_buffer, &buffer_size, stdin);

        // Eliminamos el carácter de nueva línea del final
        input_buffer[strcspn(input_buffer, "\n")] = '\0';

        // Parseamos el comando
        char *command = strtok(input_buffer, " ");

        if (command == NULL)
        {
            continue; // Comando vacío, volvemos a pedir entrada
        }

        // Ejecutamos el comando correspondiente
        if (strcmp(command, "pwd") == 0)
        {
            pwd();
        }
		else if (strcmp(command, "echo") == 0)
        {
            char *arg = strtok(NULL, " ");
            while (arg != NULL)
            {
                printf("%s ", arg);
                arg = strtok(NULL, " ");
            }
            printf("\n");
        }
		else if (strcmp(command, "env") == 0)
        {
            execute_env(env);
        }
        else	
        {
            // Comando no reconocido
            printf("Comando no reconocido: %s\n", command);
        }
    }

    free(input_buffer);
    return 0;
}*/
