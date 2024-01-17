/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comprobar_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:05:35 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/17 19:44:57 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <ctype.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/errno.h>

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
	char	*key;
	char	*value;
	char	**env_cpy;
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
int	add_history(const char *str);
t_word *create_word(char *str, size_t len, int type);

//  PROCESOS Y DEFINICION DE LOS TIPOS DE COSAS QUE LE ENVIO

#define ARGUMENTS 0		// Palabra o argumentos normal
#define PIPE 1			// Operador o tuberia (|)
#define REDIRECT_IN 2 	// Operador de redireccion de entrad (<)
#define REDIRECT_OUT 3	// Operador de redireccion de salida (>)
#define APPEND 4		// Operador de redireccion de salida en concatenacion (>>)
#define DOUBLE_INT 5	// Operador de redireccion de entrada doble (<<)

int operator_types[256] = {0};

void initialize_operator_types()
{
    operator_types['|'] = PIPE;
    operator_types['>'] = REDIRECT_OUT;
    operator_types['<'] = REDIRECT_IN;
    operator_types['2'] = APPEND;  // '2' representa ">>"
	operator_types['3'] = DOUBLE_INT;
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
	while (*str)
    {
        if ((*str == '>' || *str == '<' || *str == '|') &&
            (str[1] == '>' || str[1] == '<' || str[1] == '|' || str[1] == '\0'))
        {
            printf("syntax error near unexpected token '%c%c'\n", *str, str[1]);
            return 1;
        }
        else if (*str == '|' && (str[1] == '|' || str[1] == '>' || str[1] == '<'))
        {
            printf("syntax error near unexpected token '%c%c'\n", *str, str[1]);
            return 1;
        }
        else if ((*str == '>' || *str == '<' || *str == '|') && str[1] == '\0')
        {
            printf("syntax error near unexpected token '%c'\n", *str);
            return 1;
        }

        str++;
    }
    if (*(str - 1) == '\n')
    {
        printf("syntax error near unexpected token `newline'\n");
        return 1;
    }

    return 0;
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
	/*if (!*tokens)
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
	if ((*tokens)->error == 0)
	{
		matrixify(*tokens);
		add_history(str);
	}
	return ((*tokens)->error);*/
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
	else if (str[0] == '\'') //despues prueba poniendo esto como if
		add_words(tokens, str + 1, len, 1);
	else
		add_words(tokens, str, len, 0);
	return (len + 2);
	/*int len = dst_dots(str, str[0]);
    if (len == -1 || len == -2)
    {
        tokens->error = 1;
        return 1;
    }
    if (len == 0)
        return len;

    // Eliminar comillas dobles o simples alrededor de la palabra
    if (len >= 2 && (str[0] == '"' || str[0] == '\'') && str[0] == str[len - 1])
    {
        add_words(tokens, str + 1, len - 2, 0);
    }
    else
    {
        add_words(tokens, str, len, 0);
    }

    return len + 2;*/
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

int	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*s++)
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	int		i;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *) malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	add_words(t_tokens *tokens, char *str, size_t len, int type)
{
	/*if (type == 2 || type == 1)
    {
		if (len >= 2 && (str[0] == '"' || str[0] == '\'') && str[0] == str[len - 1])
		{
			str++;
			len -= 2;
		}
    }
    t_word *new_word = create_word(str, len, type);
    if (!new_word)
        return 0;

    tokens->size += 1;
    t_word *new_array = realloc(tokens->words, tokens->size * sizeof(t_word));
    if (!new_array)
    {
        free(new_word->word);
        free(new_word);
        return 0;
    }
    new_array[tokens->size - 1] = *new_word;
    tokens->words = new_array;
    free(new_word);
    return 1;*/
	t_word *new_word = create_word(str, len, type);
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
	return (1);
    /*if (type == ARGUMENTS)
    {
        // Ajustar la lógica para reconocer correctamente ">>" como APPEND
        if (len >= 2 && str[0] == '>' && str[1] == '>')
        {
            type = APPEND;
            len = 2; // Ajustar la longitud para ">>"
        }
        else
        {
            type = operator_types[(unsigned char)str[0]];
        }
    }

    // Copiar la cadena y eliminar comillas si existen alrededor
    char *word_copy = ft_strdup(str);
    if (!word_copy)
        return 0;
	t_word *new_word = create_word(word_copy, strlen(word_copy), type);
    free(word_copy); // Liberar la copia después de usarla
    if (!new_word)
        return 0;

    size_t new_size = tokens->size + 1;

    t_word *new_array = (t_word *)malloc(new_size * sizeof(t_word));
	if (!new_array)
    {
        free(new_word->word);
        free(new_word);
        return 0;
    }
	memcpy(new_array, tokens->words, tokens->size * sizeof(t_word));

    // Agregar la nueva palabra al final del nuevo array
    new_array[tokens->size] = *new_word;

    // Liberar el antiguo array y actualizar la referencia
    free(tokens->words);
    tokens->words = new_array;
    tokens->size = new_size;
    free(new_word);*/
    //tokens->words = new_array;
    //tokens->words[tokens->size] = *new_word;
    //tokens->size = new_size;
    //free(new_word);
    //return 1;
}

char	*ft_substr(char const *s, unsigned int start, size_t len);

t_word *create_word(char *str, size_t len, int type)
{
    t_word *word = (t_word *)malloc(sizeof(t_word));
    
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
    while (len-- > 0)
	{
       word->word[len] = str[len];
	}
    return (word);
   /*t_word *word = malloc(sizeof(t_word));
    if (!word)
        return NULL;
	word->word = strdup(str);
    if (!word->word) {
        free(word);
        return NULL;
    }

    word->len = len;
    word->type = type;
    return word;*/
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
		tokens->env[i] = ft_strdup(word[i].word);
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
	/*if (!format_str)
    {
		printf("{%d}:", word.type);
		if (word.type == 1 || word.type == 2)
			printf(" >>%s<<\n", word.word);
		else
			printf(" %s\n", word.word);
    }
    else
    {
        if (word.type == 1 || word.type == 2)
            printf(format_str, word.word);
        else
            printf(format_str, word.word);
    }*/
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
		printf("%d ", operator_types[(unsigned char)tokens->words[i].word[0]]);
		i++;
	}
	printf("\n");
}

/*void	signal_ctrl_c(int sig)
{
	if (sig == SIGINT) //esto le indica que interrumpe el programa;
	{
		printf("\n");
		rl_on_new_line(); // esto indica que el cursor debe moverse a una nueva linea;
		rl_replace_line("", 0); // reemplaza el antiguo texto con uno nuevo
		rl_redisplay(); // muestra lo escrito por la funcion anterior.
	}
}

void	signals(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN); //esta linea maravillosa hace que le meta un null al readline y al hacer un ctrl-D, le mete ese null dentro del readline y hace un exit(1);
	signal(SIGINT, signal_ctrl_c);
}*/

/*void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}*/

int pwd(void)
{
    char *pwd = getcwd(NULL, 0);
    if (pwd != NULL)
    {
        printf("%s\n", pwd);
        free(pwd);
        return 0;  // Éxito
    }
    else
    {
        printf("Error: Mano el 'pwd' no funca 🤒\n");
        return 1;  // Error
    }
}
	/*		COMIENZO DEL EXIT		*/

// al hacer '$?' despues de un exit significa que te dara un valor es decir:
// dara 0: en caso de exito, que indica que el comando se ejecuto sin errores.
// ejemplo:
// 			echo "hola como estan?"
// 			hola como estan
// 			echo $?
// 			0
// dara 1-125: significa que dio errores generales o condiciones de salida anormales.
// ejemplo:
// 			ls archivo_inexistente
// 			ls: archivo_inexistente: No such file or directory
// 			echo $?
// 			1
// dara 126: significa que no se puede ejecutar el comando. Puede deberse a permisos insuficientes, el comando no encontrado, etc.
// ejemplo:
// 			./mi_script.sh
//			bash: ./mi_script.sh: Permission denied
//			echo $?
//			126
// dara 127: cuando el comando no pude ser encontrado.
// ejemplo:
// 			horse
// 			bash: horse: command not found
// 			echo $?
// 			127

	/*		OTROS EJEMPLOS		*/

// EL NOMBRE DE "$?" ES "STATUS VARIABLE" o "VARIABLE DE ESTADO"
// "STATUS VARIABLE" ➜ Es una variable especial que almacena el código de salida del último comando ejecutado en la terminal.
//bash-3.2$: exit 123 (LO QUE LE ENVIAMOS)
//exit (RESULTADO)
//➜  Desktop echo $? (STATUS VARIABLE ➜ "$?")
//123 (EL RESULTADO QUE DA) (AUN FALTA COMPRENDER)
//
//bash-3.2$: exit 123 456 (LO QUE LE ENVIAMOS)
//exit (RESULTADO)
//bash: exit: too many arguments (RESULTADO DE BASH)
//bash-3.2$ echo $? (STATUS VARIABLE ➜ "$?")
//1 (AQUI SE CUMPLE EL ERROR DE 1-125)

/*int	echo(char **args)
{
	bool	print_line;

	print_line = true;
	if (strncmp(*args, "echo", strlen(*args)) != 0)
		return (EXIT_FAILURE);
	args++;
	if (*args && strncmp(*args, "-n", strlen("-n") + 1) == 0)
	{
		print_line = false;
		args++;
	}
	while (*args != NULL)
	{
		printf("%s", *args);
		args++;
		if (*args != NULL)
			printf(" ");
	}
	if (print_line)
		printf("\n");
	return (EXIT_SUCCESS);
}*/
/*static int	ft_count_char(const char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}*/

int echo(const char **args)
{
	    bool print_line = true;
    args++; // Avanzar al primer argumento después de "echo"

    if (*args && strncmp(*args, "-n", strlen("-n") + 1) == 0)
    {
        print_line = false;
        args++;
    }

    while (*args != NULL)
    {
        const char *arg = *args;
        size_t arg_len = strlen(arg);

        if (arg_len >= 2 && ((arg[0] == '"' && arg[arg_len - 1] == '"') || (arg[0] == '\'' && arg[arg_len - 1] == '\'')))
        {
            // Si la cadena comienza y termina con comillas simples o dobles, imprímela sin las comillas
            printf("%.*s", (int)arg_len - 2, arg + 1);
        }
        else
        {
            // Si no, imprimir la cadena normalmente
            // Eliminar comillas dentro de la cadena
            const char *quote = strpbrk(arg, "\"\'");
            while (quote != NULL)
            {
                size_t chunk_len = quote - arg;
                printf("%.*s", (int)chunk_len, arg);

                arg = quote + 1; // Saltar la comilla encontrada
                quote = strpbrk(arg, "\"\'");
            }

            // Imprimir el resto de la cadena
            printf("%s", arg);
        }

        args++;

        if (*args != NULL)
            printf(" ");
    }

    if (print_line)
        printf("\n");

    return 0; // Éxito
	/*bool print_line = true;
    args++;

    if (*args && strcmp(*args, "-n") == 0)
    {
        print_line = false;
        args++;
    }

    while (*args != NULL)
    {
        // Manejo de comillas
        const char *arg = *args;
        size_t arg_len = strlen(arg);

        if (arg_len >= 2 && ((arg[0] == '"' && arg[arg_len - 1] == '"') || (arg[0] == '\'' && arg[arg_len - 1] == '\'')))
        {
            // Si la cadena comienza y termina con comillas simples o dobles, imprímela sin las comillas
            printf("%.*s", (int)arg_len - 2, arg + 1);
        }
        else
        {
            // Si no, imprime la cadena normalmente
            printf("%s", arg);
        }

        args++;

        if (*args != NULL)
            printf(" ");
    }

    if (print_line)
        printf("\n");

    return EXIT_SUCCESS;*/
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	ft_env(char *input, t_env *count)
{
	int i = 0;
	
	if (ft_strcmp(input, "env") == 0)
	{
		while (count->env_cpy[i])
		{
			printf("%s\n", count->env_cpy[i]);
			i++;
		}
	}
}

void	print_export(t_env *env)
{
	while (env->key != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env++;
	}
}

void	update_env_copy(t_env *env)
{
	size_t env_size = 0;
	while (env[env_size].key != NULL)
		env_size++;
	free(env->env_cpy);
	env->env_cpy = malloc((env_size + 1) * sizeof(char *));
	size_t i = 0;
	while (env[i].key != NULL)
	{
		env->env_cpy[i] = env[i].key;
		i++;
	}
	env->env_cpy[i] = NULL;
}

void	set_export(t_env *env, const char *key, const char *value)
{
	while (env->key != NULL)
	{
		if (strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = strdup(value);
			update_env_copy(env);
			return;
		}
		env++;
	}
	env->key = strdup(key);
	env->value = strdup(value);
	(env + 1) ->key = NULL;
	update_env_copy(env);
}

void	export_command(t_env *env, const char *arg)
{
	const char *equal_signo = strchr(arg, '=');
	
	if (!equal_signo || equal_signo == arg)
	{
		printf("Error papu\n");
		return;
	}
	size_t	key_len = equal_signo - arg;
	char	*key = strndup(arg, key_len + 1);
	char	*value = ft_strdup(equal_signo + 1);

	int i = 0;

	while(env[i].key != NULL)
	{
		if (strncmp(env[i].key, key, key_len) == 0 && env[i].key[key_len] == '=')
		{
			free(env[i].value);
			env[i].value = ft_strdup(value);
			free(key);
			free(value);
			printf("Updated variable: %s=%s\n", env[i].key, env[i].value);
			return ;
		}
		i++;
	}
	//char *new_env = ft_strdup(arg);
    //if (!new_env)
    //{
      //  printf("Error: Fallo al duplicar la cadena del entorno\n");
        //free(key);
		//free(value);
        //return;
    //}
    //env[i] = new_env;
	env[i].key = strdup(key);
	env[i].value = strdup(value);
	(env + 1)->key = NULL;
	set_export(env, key, value);
	free(key);
	free(value);
	printf("Added new variable: %s=%s\n", env[i].key, env[i].value);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t s_len = strlen(s);
    if (start >= s_len)
        return NULL;
    if (start + len > s_len)
        len = s_len - start;

    char *s_str = (char *)malloc((len + 1) * sizeof(char));
    if (!s_str)
        return NULL;

    memcpy(s_str, s + start, len);
    s_str[len] = '\0';

    return s_str;
}

static char	**ft_freeall(char **tab, size_t i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static size_t	ft_splitlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

static char	**ft_split_aux(char **arr, char const *s, char c)
{
	if (!s)
		return (NULL);
	arr = calloc((ft_splitlen(s, c) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*start;
	size_t	i;

	arr = NULL;
	arr = ft_split_aux(arr, s, c);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			arr[i++] = ft_substr(start, 0, s - start);
			if (!arr[i - 1])
				return (ft_freeall(arr, i - 1));
		}
	}
	arr[i] = NULL;
	return (arr);
}
//funcion que vera si hara comandos

/*void	exit_cmd(void)
{
	printf("No te vayas quedate, conmigo... 😞\n");
	exit(0);
}*/

void	is_command(char *input, int error, t_env *env)
{
	/*if (error)
		return;
	if (strcmp(input, "pwd") == 0)
	{
		pwd();
		printf("Comando ejecutado perrooooooo😎\n");
	}
	char **args;
	args = ft_split(input, ' ');
	if (args[0] != NULL)
	{
		if (strcmp(args[0], "echo") == 0)
		{
			const char **const_args = (const char **)args;
            echo(const_args);
			printf("Uyyyy papi comando ejecutado 🥵\n");
		}
		else if (strcmp(args[0], "export") == 0)
		{
			export_command(ft_env, *args);
			printf("Uyyy perro ese export se ejecuto bien 🤑\n");
		}
	}*/
	if (error)
		return ;

	if (strcmp(input, "pwd") == 0)
	{
		pwd();
		printf("Comando ejecutado perrooooooooo 😎\n");
	}
	else
	{
		char **args;
		args = ft_split(input, ' ');
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "echo") == 0) //es un int
			{
				const char **const_args = (const char **)args;
            	echo(const_args);
				printf("Uyyyy papi comando ejecutado 🥵\n");
			}
			else if (strcmp(args[0], "export") == 0)
			{
				export_command(env, args[1]);
				printf("Uyyy perro ese export funciona 🤑\n");
			}
			else if (strcmp(args[0], "env") == 0)
			{
				ft_env(input, env);
				printf("Uyyy ese env funca ehh 😈\n");
			}
			char	**arg_ptr = args;
			while (*arg_ptr != NULL)
			{
				free(*arg_ptr);
				arg_ptr++;
			}
			free(args);
		}
	}
}
// NO ELIMINAR ESTE MAIN ꜜ
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_tokens	*tokens = NULL;
	char		*input;
	int			err;
	t_env		my_env;
	my_env.env_cpy = env;

	
	initialize_operator_types();
	//signals();
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(0);
		
		err = parser(&tokens, input, env);
		if (tokens != NULL)
		{
			is_command(input, err, &my_env);
			//free_tokens(tokens); este free_tokens no porque ya liberamos en el parser;
			// igualamos tokens a NULL;
		}
		// hacer una o mas funciones que haga los comandos(cmd);
	}
	//free_all();
	return (0);
}

/*		MAIN PARA CONFIRMAR PARSER SI FUNCIONA CORRECTAMENTE	*/

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
