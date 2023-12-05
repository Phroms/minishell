/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2023/12/05 21:21:06 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	t_tokens *tokens = init_token(NULL);
    while (1)
	{
		input = readline("> ");
		if (!input)
			exit(0);
		if (input)
		{
			printf("Texto ingresado: %s\n", input);
			if (parser(tokens, input) == 42)
			{
				fprintf(stderr, "Error en la entrada.\n");
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
						command.args = NULL;
						command.args = malloc(sizeof(char *) * 2);
						if (!command.args)
						{
							fprintf(stderr, "Error asignando memoria para command.args\n");
							free_tokens(tokens);
							free(input);
							exit(EXIT_FAILURE);
						}
						command.args[0] = strdup(current_word->word);
						command.args[1] = NULL;
						if (command.args[0] && access(command.args[0], X_OK) == 0)
						{
							execute_command(&command, env);
							free(command.args[0]);
							free(command.args);
						}
						else
						{
							fprintf(stderr, "Comando no valido: %s\n", current_word->word);
						}
					}
					i += 1;
				}
			}
		}
		free_tokens(tokens);
		free(input);
	}
	return (0);
}

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


/*	IDEASSSSS */

typedef struct s_ShellData
{
    t_tokens tokens;
    t_env **env;
    t_word *words;
}t_ShellData;


void init_shell_data(ShellData *shell, char **env)
{
    // Inicializar la estructura t_tokens
    shell->tokens.words = NULL;
    shell->tokens.size = 0;
    shell->tokens.str = NULL;
    shell->tokens.env = NULL;
    shell->tokens.error = 0;

    // Inicializar la estructura t_env
    // ...

    // Inicializar la estructura t_word
    // ...

    // Inicializar otras variables según sea necesario
}

void free_shell_data(ShellData *shell)
{
    // Liberar memoria de la estructura t_tokens
    // ...

    // Liberar memoria de la estructura t_env
    // ...

    // Liberar memoria de la estructura t_word
    // ...

    // Liberar otras variables según sea necesario
}

int main(int argc, char **argv, char **env)
{
    ShellData shell;
    init_shell_data(&shell, env);

    // Operaciones con la nueva estructura ShellData
    // ...

    free_shell_data(&shell);
    return 0;
}
