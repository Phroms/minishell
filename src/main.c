/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:46:28 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/14 19:30:28 by agrimald         ###   ########.fr       */
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
bool special_char(char corr);
void free_tokens(t_tokens *tokens);

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
			t_tokens *tokens = init_token(NULL);
			if (add_words(tokens, input, ft_strlen(input), 0))
			{
				if (tokens->size > 0)
				{
					printf("Palabra: %s\n, Tipo: %d\n", tokens->words[0].word, tokens->words[0].type);
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
					}
				}
			}
			free_tokens(tokens);
            free(input);
		}
	}
	return (0);
}
