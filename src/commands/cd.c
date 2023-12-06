/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:51:53 by ojimenez          #+#    #+#             */
/*   Updated: 2023/11/27 15:53:53 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//usar chdir para movernos entre directorios
//idea: podemos distinguir entre el caso de que sea para delante o para atras. Si es para delante
//podemos poner en el path lo que el usuario escriba para ir a los siguientes directorios. Si es 
//para atras podemos obtener el path con getcwd y quitarle info

char	*ft_strcat(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = s1;
	while (s1[i])
		i++;
	str[i] = '/';
	i++;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*remove_end(char *str)
{
	int		i;
	int		j;
	char	*pwd_f;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	i--;
	while (i > 0 || str[i] == '/')
		i--;
	pwd_f = malloc (i * sizeof(char));
	if (!pwd_f)
		exit(EXIT_FAILURE);
	while (j < i)
	{
		pwd_f[j] = str[j];
		j++;
	}
	pwd_f[j] = '\0';
	return (pwd_f);
}

//Caso de ir hacia atras
char	*cd_back(void)
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
char	*cd_forward(char **args)
{
	char	*pwd_i;
	char	*pwd_f;

	pwd_i = getcwd(NULL, 0);
	if (!pwd_i)
	{
		perror("get_cwd");
		exit(EXIT_FAILURE);
	}
	pwd_f = malloc((ft_strlen(pwd_i) + ft_strlen(*args)) * sizeof(char));
	if (!pwd_f)
		exit(EXIT_FAILURE);
	pwd_f = ft_strcat(pwd_i, *args);
	free (pwd_i);
	return (pwd_f);
}

int	cd(char **args)
{
	int		flag;
	char	*pwd_i;
	char	*pwd_f;

	if (ft_strncmp(*args, "cd", ft_strlen(*args)) != 0)
		return (EXIT_FAILURE);
	args++;
	pwd_i = getcwd(NULL, 0);
	if (ft_strncmp(*args, "..", ft_strlen(*args)) == 0)
		pwd_f = cd_back();
	else
		pwd_f = cd_forward(args);
	flag = chdir(pwd_f);
	free(pwd_f);
	if (flag == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
