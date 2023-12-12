/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comprobar_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:05:35 by agrimald          #+#    #+#             */
/*   Updated: 2023/12/12 18:45:30 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <ctype.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>

// Estructuras

typedef struct s_word
{
	char		*word;
	size_t		len;
	int			type;
}	t_word;

typedef struct s_tokens
{
	t_word	*words;
	size_t	size;
	char	*str;
	char	**env;
	int		error;
}	t_tokens;

typedef struct s_env
{
	char	*env_cpy;
}	t_env;



typedef struct s_pcs
{
	int			*types;
	t_tokens	*argv;
}	t_pcs;



// Funciones
int special_char(char c);
int dst_dots(char *str, char dot);
int add_words(t_tokens *tokens, char *str, size_t len, int type);
int is_marks(t_tokens *tokens, char *str);
int is_space(t_tokens *tokens, char *str);
t_tokens *init_token(char **env);
int matrixify(t_tokens *tokens);
void add_history(char *str);
t_word *create_word(char *str, size_t len, int type);

//  PROCESOS Y DEFINICION DE LOS TIPOS DE COSAS QUE LE ENVIO

#define ARGUMENTS 0		// Palabra o argumentos normal
#define PIPE 1			// Operador o tuberia (|)
#define REDIRECT_IN 2 	// Operador de redireccion de entrad (<)
#define REDIRECT_OUT 3	// Operador de redireccion de salida (>)
#define APPEND 4		// Operador de redireccion de salida en concatenacion (>>)

int operator_types[256] = {0};

void initialize_operator_types()
{
    operator_types['|'] = PIPE;
    operator_types['>'] = REDIRECT_OUT;
    operator_types['<'] = REDIRECT_IN;
    operator_types['2'] = APPEND;  // '2' representa ">>"
}

int	is_rd(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int is_redirection(char *str, int i)
{
	if (str[i + 1] == '\0')
		return (1);
	if (i < 2)
		return (0);
	if (is_rd(str[i - 1]) && is_rd(str[i - 2]) && is_rd(str[i]))
		return (1);
	if (str[i] == '<' && str[i - 1] == '>')
		return (1);
	return (0);
}

int	check_rd(char *str, int i)
{
	if (str[i] == '<' || str[i] == '>')
		return (1);
	if (str[i + 1] == '\0')
		return (1);
	if (str[i - 1] == '<' || str[i - 1] == '>')
		return (1);
	return (0);
}

int	check_input(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<') //|| str[i] == '|')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
			{
				printf("syntax error near unexpected token '%c'\n", str[i]);
				return 1;
			}
		}
		else if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				printf("syntax error near unexpected token '|'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	break_token(t_tokens *tokens, char *str)
{
	add_words(tokens, str, 1, 3);
	return (1);
}

int	is_normal_ch(char ch)
{
	if (special_char(ch) || ch == '#' || ch == '"' \
			|| ch == ' ' || ch == '\'')
		return (1);
	return (0);
}

int	string_tokens(t_tokens *tokens, char *str)
{
	int	i;
	int	command_found;

	i = 0;
	command_found = 0;
	while (str[i] && !is_normal_ch(str[i]))
		i++;
	if (!command_found)
		add_words(tokens, str, i, 0);
	return (i);
}

int	parse_string(t_tokens *tokens, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '#')
	{
		if (special_char(str[i]))
			i += break_token(tokens, str + i);
		else if (str[i] == '"' || str[i] == '\'')
			i += is_marks(tokens, str + i);
		else if (str[i] == ' ')
			i += is_space(tokens, str + i);
		else
			i += string_tokens(tokens, str + i);
		if (tokens->error == 1)
			return (1);	
		j++;
	}
	return (0);
}

int	parser(t_tokens **tokens, char *str, char **env)
{
	if (!*tokens)
	{
		*tokens = init_token(env);
		if (!*tokens)
		{
			printf("Error: oe tu token no funciona\n");
			return (1);
		}
	}
	(*tokens)->env = env;
	(*tokens)->error = 0;
	if (check_input(str))
		return (42);
	parse_string(*tokens, str);
	matrixify(*tokens);
	if ((*tokens)->error == 0)
		add_history(str);
	return ((*tokens)->error);
}

int	special_char(char c)
{
	if (c == '$' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	dst_dots(char *str, char dot)
{
	int	i;

	i = 1;
	if (str[1] == '\0')
	{
		printf("Error hay null oe\n");
		return (-1);
	}
	if (str[1] == dot)
		return (-2);
	while (str[i] && str[i] != dot)
		i++;
	if (str[i] == '\0')
	{
		printf("error not closing marks\n");
		return (-1);
	}
	return (i - 1);
}

int	is_marks(t_tokens *tokens, char *str)
{
	int	len;

	len = dst_dots(str, str[0]);
	if (len == -1 || len == -2)
	{
		tokens->error = 1;
		return (1);
	}
	if (len == 0)
		return (len);
	if (str[0] == '"')
		add_words(tokens, str + 1, len, 2);
	if (str[0] == '\'')
		add_words(tokens, str + 1, len, 1);
	return (len + 2);
}

int	is_space(t_tokens *tokens, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	add_words(tokens, " ", 1, 4);
	return (i);
}

t_tokens	*init_token(char **env)
{
	t_tokens *tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->words = NULL;
	tokens->size = 0;
	tokens->env = env;
	return (tokens);
}

int	add_words(t_tokens *tokens, char *str, size_t len, int type)
{
    /*t_word *new_word = create_word(str, len, type);
    if (!new_word)
		return 0;
	tokens->size += 1;
    t_word *new_array = calloc(tokens->size, sizeof(t_word));
    if (!new_array)
	{
        free(new_word->word);
        free(new_word);
        return 0;
    }
    if (tokens->size > 1)
	{
        memcpy(new_array, tokens->words, (tokens->size - 1) * sizeof(t_word));
		free(tokens->words);
	}
	new_array[tokens->size - 1] = *new_word;
	//free(tokens->words);
	tokens->words = new_array;
	//free(new_word->word);
	free(new_word);
	return (1);*/
    if (type == ARGUMENTS)
    {
        // Ajusta la lógica para reconocer correctamente ">>" como APPEND
        if (len >= 2 && str[0] == '>' && str[1] == '>')
        {
            type = APPEND;
        }
        else
        {
            type = operator_types[str[0]];
        }
    }

    t_word *new_word = create_word(str, len, type);
    if (!new_word)
        return 0;

    size_t new_size = tokens->size + 1;

    t_word *new_array = malloc(new_size * sizeof(t_word));
    if (!new_array)
    {
        free(new_word->word);
        free(new_word);
        return 0;
    }

    if (tokens->words)
    {
        memcpy(new_array, tokens->words, tokens->size * sizeof(t_word));
        free(tokens->words);
    }

    new_array[tokens->size] = *new_word;
    tokens->words = new_array;
    tokens->size = new_size;

    free(new_word);

    return 1;
}

t_word *create_word(char *str, size_t len, int type)
{
    t_word *word = malloc(sizeof(t_word));
	//size_t i;

	//i = 0;
    if (!word)
        return NULL;

    word->word = calloc(len + 1, sizeof(char));
    if (!word->word)
    {
        free(word);
        return NULL;
    }

    word->len = len;
    word->type = type;
    //word->next = NULL;
    //word->word[len] = '\0';

    while (len-- > 0)
	{
        word->word[len] = str[len];
		//i++;
	}
    return word;
}
int	matrixify(t_tokens *tokens)
{
	t_word *word;
	size_t i;

	word = tokens->words;
	if (!word)
		return 0;

	tokens->env = (char **)calloc(tokens->size + 1, sizeof(char *));
	if (!tokens->env)
		return 0;

	i = 0;
	while (i < tokens->size)
	{
		tokens->env[i] = strdup(word[i].word);
		if (!tokens->env[i])
			return 0;
		/*memcpy(tokens->env[i]->env_cpy, word[i].word, word[i].len);
		tokens->env[i]->env_cpy[word[i].len] = '\0';*/
		i++;
	}
	return (1);
}

void	free_tokens(t_tokens *tokens)
{
	if (tokens)
	{
        free(tokens->words);
        free(tokens);
    }	
}

void	print_wrd_format(char *format_str, t_word word)
{
	if (!format_str)
		printf("{%d}%s<", word.type, word.word);
	else
		printf(format_str, word.type, word.word);
}

void	print_tokens(t_tokens *tokens)
{
	size_t	i;

	i = 0;
	while (i < tokens->size)
	{
		print_wrd_format("%d: >>%s<<\n", tokens->words[i]);
		i += 1;
	}
}

int	free_tokens_memory(t_tokens *tokens)
{
	size_t	i;
	t_word	*word;
	//t_word	*aux;

	i = 0;
	while (tokens->words)
	{
		word = &tokens->words[i];
		free(word->word);
		i++;
	}
	free(tokens->words);
	free(tokens);
	return (1);
}

void	print_pcs_recur(t_pcs *pcs, size_t index)
{
	if (!pcs || !pcs->argv || index >= pcs->argv->size)	
		return ;

	if (pcs->types)
		printf("Tipo: %d - Arguments: %s\n", pcs->types[index], pcs->argv->words[index].word);
	else
		printf("Tipo: -1 - Arguments: %s\n", pcs->argv->words[index].word);

	print_pcs_recur(pcs, index + 1);	
}

void	print_pcs(t_pcs *pcs)
{
	if (!pcs || !pcs->argv || pcs->argv->size == 0 || !pcs->argv->words)
	{
		printf("Oe payaso no hay nada 🤡\n");
		return ;
	}
	printf("Procesos:\n");
	print_pcs_recur(pcs, 0);
}

void	print_pcs_types(t_tokens *tokens, int operator_types[])
{
	if (!tokens || !tokens->words)
	{
		printf("No hay tipos asociados a pcs. gil:\n");
		return ;
	}
	printf ("Aqui si hay tipos asociados a pcs wapo:\n");
	size_t i = 0;
	while (i < tokens->size)
	{
		printf("%d ", operator_types[tokens->words[i].word[0]]);
		i++;
	}
	printf("\n");
}

int main()
{
    char *env[] = {"VAR1=value1", "VAR2=value2", NULL}; // Ejemplo de entorno

    // Inicializar el array de tipos de operadores
    initialize_operator_types();

    t_tokens *tokens = NULL;
    char input[256]; // Puedes ajustar el tamaño según tus necesidades

    printf("Ingresa una cadena: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n\r")] = '\0'; // Elimina salto de línea y retorno de carro

    int result = parser(&tokens, input, env);

    if (result == 0)
    {
        printf("Tokens generados:\n");
        print_tokens(tokens);
        t_pcs procesos;
        procesos.argv = tokens;
        procesos.types = NULL;
        if (tokens && tokens->size > 0 && tokens->error == 0)
            procesos.types = &tokens->words[0].type;
        print_pcs_types(procesos.argv, operator_types);
    }
    else
    {
        printf("Error durante el análisis de la cadena.\n");
    }

    // Liberar memoria si es necesario
    free_tokens(tokens);

    return 0;
}

/*int main()
{
    char *env[] = {"VAR1=value1", "VAR2=value2", NULL}; // Ejemplo de entorno

    // Inicializar el array de tipos de operadores
    initialize_operator_types();

    t_tokens *tokens = NULL;
    char input[256]; // Puedes ajustar el tamaño según tus necesidades

    printf("Ingresa una cadena: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n\r")] = '\0'; // Elimina salto de línea y retorno de carro

    int result = parser(&tokens, input, env);

    if (result == 0)
    {
        printf("Tokens generados:\n");
        print_tokens(tokens);

        // Imprimir tipos de tokens
        printf("Tipos de tokens generados:\n");
        for (size_t i = 0; i < tokens->size; ++i)
        {
            printf("%d ", tokens->words[i].type);
        }
        printf("\n");

        t_pcs procesos;
        procesos.argv = tokens;
        procesos.types = NULL;
        if (tokens && tokens->size > 0 && tokens->error == 0)
            procesos.types = &tokens->words[0].type;
        print_pcs_types(procesos.argv, operator_types);
    }
    else
    {
        printf("Error durante el análisis de la cadena.\n");
    }

    // Liberar memoria si es necesario
    free_tokens(tokens);

    return 0;
}*/
