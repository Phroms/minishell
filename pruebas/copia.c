/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comprobar_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:05:35 by agrimald          #+#    #+#             */
/*   Updated: 2024/01/26 18:40:34 by agrimald         ###   ########.fr       */
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
	int	command_found;

	i = 0;
	j = 0;
	command_found = 0;

	while (str[i] && str[i] != '#')
	{
		if (special_char(str[i]))
			i += break_token(tokens, str + i);
		else if (str[i] == '"' || str[i] == '\'')
			i += is_marks(tokens, str + i);
		else if (str[i] == ' ')
			i += is_space(tokens, str + i);
		else
		{
			if (!command_found)
			{
				command_found = 1;
				j = string_tokens(tokens, str + i);
			}
			else
			{
				j = i;
				while (str[i] && !is_normal_ch(str[j]))
					j++;
				add_words(tokens, str + i, j - i, ARGUMENTS);
				i = j - 1;
			}
		}
		if (tokens->error == 1)
			return (1);
		i++;
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
	else if (str[0] == '\'') //despues prueba poniendo esto como if
		add_words(tokens, str + 1, len, 1);
	else
		add_words(tokens, str, len, 0);
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
			printf("%.*s", (int)arg_len - 2, arg + 1);
        }
        else
        {
            const char *quote = strpbrk(arg, "\"\'");
            while (quote != NULL)
            {
                size_t chunk_len = quote - arg;
                printf("%.*s", (int)chunk_len, arg);

                arg = quote + 1; // Saltar la comilla encontrada
                quote = strpbrk(arg, "\"\'");
            }
            printf("%s", arg);
        }

        args++;

        if (*args != NULL)
            printf(" ");
    }

    if (print_line)
        printf("\n");

    return 0;
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

#define TRUE 1
#define FALSE 0

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

void	hola(char **env, t_env *env_hola)
{
	int i = 0;
	int j = 0;

	while (env[i] != NULL)
		i++;
	env_hola->env_cpy = calloc(sizeof(char *), i + 1);
	if (!env_hola->env_cpy)
		exit(1);
	while (j < i)
	{
		env_hola->env_cpy[j] = strdup(env[j]);
		j++;
	}
	env_hola->env_cpy[j] = NULL;
}

int	mod_strcmp(char *cmd, char *env)
{
	int	i = 0;

	while (cmd[i] && env[i])
	{
		if (cmd[i] == '=' && env[i] == '=')
			return (TRUE);
		if (cmd[i] != env[i])
			return (FALSE);
		i++;
	}
	if (cmd[i] == '\0' && (env[i] == '\0' || env[i] == '='))
		return (TRUE);
	return (FALSE);
}

void	bubble_sort(char **arr, int size, int i);
void	normal_export(char *cmd, t_env *env);

void	replace_value(char *cmd, t_env *env)
{
	int i = 0;

	while (env->env_cpy[i] != NULL)
	{
		if (mod_strcmp(cmd, env->env_cpy[i]) == TRUE)
		{
			free(env->env_cpy[i]);
			env->env_cpy[i] = strdup(cmd);
			//sort_env(env, i + 1, 0);
			return;
		}
		i++;
	}
	normal_export(cmd, env);
}

int	var_exist(char *cmd, t_env *env)
{
	int i = 0;

	while (env->env_cpy[i] != NULL)
	{
		if (mod_strcmp(cmd, env->env_cpy[i]) == TRUE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	bubble_sort(char **arr, int size, int i)
{
	if (i == size - 1)
		return;
	if (strcmp(arr[i], arr[i + 1]) > 0)
	{
		char *tmp = arr[i];
		arr[i] = arr[i + 1];
		arr[i + 1] = tmp;
	}
	bubble_sort(arr, size, i + 1);
}
void	print_special_export(t_env *env, int count, int i)
{
	if (i < count)
	{
		printf("declare -x %s\n", env->env_cpy[i]);
		print_special_export(env, count, i + 1);
	}
}

void	special_export(t_env *env)
{
	int i = 0;

	while (env->env_cpy[i] != NULL)
	{
		char *equal_sign = strchr(env->env_cpy[i], '=');
		if (equal_sign != NULL)
        {
			*equal_sign = '\0';
            printf("declare -x %s=\"%s\"\n", env->env_cpy[i], equal_sign + 1);
            *equal_sign = '=';
		}
		else
		{
			 printf("declare -x %s\n", env->env_cpy[i]);
		}
		i++;
	}
}

void	normal_export(char *cmd, t_env *env)
{
	int i = 0;
	char **nuria;

	nuria = env->env_cpy;
	while (env->env_cpy[i] != NULL)
		i++;
	env->env_cpy = calloc(sizeof(char *), i + 2);
	int j = 0;
	while (j < i)
	{
		env->env_cpy[j] = strdup(nuria[j]);
		free(nuria[j]);
		j++;
	}
	env->env_cpy[j++] = strdup(cmd);
	env->env_cpy[j] = NULL;
	free(nuria);
}

void	ft_export(t_env *env, char **cmd)
{
	int i = 0;
	if (cmd[0] == NULL)
		special_export(env);
	else
	{
		while (cmd[i] != NULL)
		{
			if (strcmp(cmd[i], "0") == 0)
			{
				printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
			}
			else
			{
				if (var_exist(cmd[i], env) == TRUE)
					replace_value(cmd[i], env);
				else
					normal_export(cmd[i], env);
			}
			i++;
		}
	}
}

void	ft_unset(char *variable, t_env *env)
{
	int i = 0;
	char **env_ptr = env->env_cpy;

	while (env_ptr[i] != NULL)
	{
		if (strncmp(env_ptr[i], variable, strlen(variable)) == 0)
		{
			while (env_ptr[i] != NULL)
			{
				env_ptr[i] = env_ptr[i + 1];
				i++;
			}
			return;
		}
		i++;
	}
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
void	is_command(char *input, int error, t_env *env)
{
   	if (error)
        return;

    char **args;
    args = ft_split(input, ' ');

    if (args[0] != NULL)
    {
        if (strcmp(input, "pwd") == 0)
        {
            pwd();
            printf("Comando ejecutado perrooooooooo 😎\n");
        }
        else if (strcmp(args[0], "echo") == 0)
        {
            const char **const_args = (const char **)args;
            echo(const_args);
            printf("Uyyyy papi comando ejecutado 🥵\n");
        }
        else if (strcmp(args[0], "export") == 0)
        {
            ft_export(env, &args[1]);
            printf("Uyyy perro ese export funciona 🤑\n");
        }
        else if (strcmp(args[0], "env") == 0)
        {
            ft_env(input, env);  // Solo pasamos la estructura de entorno
            // No imprima un mensaje aquí para `env`
        }
        else if (strcmp(args[0], "unset") == 0)
        {
            if (args[1] != NULL)
            {
                ft_unset(args[1], env);
                printf("Uyyy ese unset esta hot hot 😳\n");
            }
            else
                printf("Oe payaso no hay nada despues del unset 🤡\n");
        }

        char **arg_ptr = args;
        while (*arg_ptr != NULL)
        {
            free(*arg_ptr);
            arg_ptr++;
        }
        free(args);
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

	hola(env, &my_env);
	initialize_operator_types();
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(0);



		err = parser(&tokens, input, env);
		if (err == 0 && tokens->size > 0)
			{
				is_command(tokens->words[0].word, err, &my_env);
			}
		else if (err != 0)
			printf("Error: hey aqui no funciono correctame 😓\n");
	}
	free_tokens(tokens);
	tokens = NULL;
	free(input);
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
