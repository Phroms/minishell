/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:19:59 by agrimald          #+#    #+#             */
/*   Updated: 2023/10/30 22:12:09 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../lib/minishell.h"

# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				j;

	j = 0;
	i = 0;
	if (n == 0)
		return (0);
	while (s1[j] != '\0' && s2[j] != '\0' && s1[j] == s2[j] && i < n -1)
	{
		j++;
		i++;
	}
	return ((unsigned char)s1[j] - (unsigned char)s2[j]);
}

char	*ft_strdup(const char *s1)
{
	char	*nuevo;
	int		i;

	i = 0;
	nuevo = malloc(ft_strlen(s1) + 1);
	if (nuevo == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		nuevo[i] = s1[i];
		i++;
	}
	nuevo[i] = '\0';
	return (nuevo);
}

size_t	read_variable(char *or_env)
{
	size_t	view_variable;

	view_variable = 0;
	while (or_env[view_variable])
		view_variable++;
	return (view_variable);
}

void	duplicate_env(char **env_cpy, char *or_env)
{
	unsigned int i;

	i = 0;
	while (env_cpy[i])
	{
		env_cpy[i] = ft_strdup(&or_env[i]);
		printf("og: %c\n\ncp: %s\n\n", or_env[i], env_cpy[i]);
		i++;
	}
	env_cpy[i] = NULL;
}

char	*cpy_or_env(char *or_env)
{
	char **env_cpy = NULL;

	env_cpy = (char **)malloc(sizeof(char *) * read_variable(or_env) + 1);
	duplicate_env(env_cpy, or_env);
	return (*env_cpy);
}
char	*ft_getenv(char *variable, char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		if (ft_strncmp(variable, env[i], ft_strlen(variable)) == 0 && env[i][ft_strlen(variable)] == '=')
		{
			return env[i] + ft_strlen(variable) + 1;
		}
		i++;
	}
	return NULL;
}

/*int main(int argc, char **argv, char **envp) {
    if (argc < 2) {
        printf("Uso: %s VARIABLE_DE_ENTORNO1 VARIABLE_DE_ENTORNO2 ... VARIABLE_DE_ENTORNO_N\n", argv[0]);
        return 1;
    }

    // Llamada recursiva para manejar múltiples variables de entorno
    char *variable = argv[1];
    char *valor = ft_getenv(variable, envp);

    if (valor != NULL) {
        printf("%s: %s\n", variable, valor);
    } else {
        printf("%s variable de entorno no encontrada.\n", variable);
    }

    // Llamada recursiva con el siguiente argumento
    if (argc > 2) {
        main(argc - 1, argv + 1, envp);
    }

    return 0;
}*/
