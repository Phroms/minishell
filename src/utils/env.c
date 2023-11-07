/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:19:59 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/07 16:49:17 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	int i;
	   
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(variable, env[i], ft_strlen(variable)) == 0 && env[i][ft_strlen(variable)] == '=')
		{
			return env[i] + ft_strlen(variable) + 1;
		}
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp) 
{
    if (argc < 2)
	{
        printf("Uso: %s VARIABLE_DE_ENTORNO1 VARIABLE_DE_ENTORNO2 ... VARIABLE_DE_ENTORNO_N\n", argv[0]);
        return 1;
    }

    // Llamada recursiva para manejar múltiples variables de entorno
    char *variable = argv[1];
    char *valor = ft_getenv(variable, envp);

    if (valor != NULL)
	{
        printf("%s: %s\n", variable, valor);
    }
   	else 
	{
        printf("%s variable de entorno no encontrada.\n", variable);
    }
	if (argc > 2) 
	{
        main(argc - 1, argv + 1, envp);
    }

    return 0;
}
