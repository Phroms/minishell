/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:51:53 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/08 19:40:06 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_end(char *str)
{
	int		i;
	int		j;
	char	*pwd_f;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	if (i == 0 || (i == 1 && str[0] == '/'))
		return (ft_strdup("/"));
	i--;
	while (i > 0 && str[i] != '/')
		i--;
	pwd_f = malloc ((i + 2) * sizeof(char));
	if (!pwd_f)
		exit(EXIT_FAILURE);
	while (j < i)
	{
		pwd_f[j] = str[j];
		j++;
	}
	pwd_f[j] = '/';
	j++;
	pwd_f[j] = '\0';
	return (pwd_f);
}

//Caso de ir hacia atras
static char	*cd_back(void)
{
	char	*pwd_i;
	char	*pwd_f;

	pwd_i = getcwd(NULL, 0);
	if (!pwd_i)
	{
		perror("get_cwd");
		exit(EXIT_FAILURE);
	}
	pwd_f = remove_end(pwd_i);
	free (pwd_i);
	return (pwd_f);
}

//Caso de ir hacia delante
static char	*cd_forward(char *pwd_i, char *str)
{
	char	*pwd_f;
	int		i;
	int		j;
	int		len;
	int		len_aux;

	i = -1;
	j = 0;
	len = ft_strlen(pwd_i) + ft_strlen(str) + 2;
	len_aux = ft_strlen(pwd_i);
	pwd_f = malloc(len * sizeof(char));
	if (!pwd_f)
		malloc_error();
	while (++i < len_aux)
		pwd_f[i] = pwd_i[i];
	pwd_f[i] = '/';
	i++;
	while (i < len - 1)
	{
		pwd_f[i] = str[j];
		i++;
		j++;
	}
	pwd_f[i] = '\0';
	return (pwd_f);
}

int	home(t_env *env, char *str, int len)
{
	char	*pwd;
	int		i;

	i = 0;
	if (len >= 3)
	{
		printf("cd : demasiados argumentos\n");
		return (1);
	}
	while (env->env_cpy[i])
	{
		if (strncmp(env->env_cpy[i], str, 4) == 0)
		{
			pwd = &env->env_cpy[i][5];
			chdir(pwd);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_cd(char **args, int len, t_env *env)
{
	int		flag;
	char	*pwd_i;
	char	*pwd_f;
	int		i;

	i = 0;
	if (len == 1 || len >= 3)
		return (home(env, "HOME", len));
	if (ft_strncmp(args[i], "cd", ft_strlen(*args)) != 0)
		return (EXIT_FAILURE);
	i++;
	pwd_i = getcwd(NULL, 0);
	if (ft_strncmp(*args, "..", ft_strlen(*args)) == 0)
		pwd_f = cd_back();
	else
		pwd_f = cd_forward(pwd_i, args[i]);
	flag = chdir(pwd_f);
	free(pwd_f);
	free(pwd_i);
	if (flag == -1)
	{
		printf("%s: Ueep, directorio no encontrado 😅\n", args[i]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
