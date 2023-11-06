/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:53:56 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/06 17:46:55 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
 #define MINISHELL_H

 #include <libft.h>
 //#include <readline/realine.h>  tengo que descargar la libreria.
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <signal.h>
 #include <ctype.h>
 #include <limits.h>
 #include <unstd.h>


typedef struct s_env
{
	char	*env_cpy;	
}t_env;

	/*		ENV		*/

size_t	read_variable(char *or_env);
void	duplicate_env(char **env_cpy, char *or_env);
char	*cpy_or_env(char *or_env);
char	*ft_getenv(char *variable, char **env);
int		main(int argc, char **argv, char **envp);

	/*		PWD		*/

void	pwd(void);

#endif
