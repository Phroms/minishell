/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:53:56 by agrimald          #+#    #+#             */
/*   Updated: 2023/10/30 20:51:16 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
 #define MINISHELL_H

 #include <readline/realine.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>


typedef struct s_env
{
	char	*env_cpy;	
}t_env;

	/*		ENV		*/

size_t	read_variable(char *or_env);
char	duplicate_env(char *env_cpy, char *or_env);
char	*cpy_or_env(char *or_env);
char	*ft_getenv(char variable, char *env);

