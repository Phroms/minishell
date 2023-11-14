/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:53:56 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/14 17:40:39 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
 #define MINISHELL_H

 #include "libft.h"
 #include <fcntl.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <readline/readline.h>
 #include <readline/history.h>
 #include <string.h>
 #include <signal.h>
 #include <ctype.h>
 #include <limits.h>
 #include <unistd.h>
 #include <stdbool.h>


typedef struct s_env
{
	char	*env_cpy;	
}t_env;

typedef struct s_word
{
	char	*word;
	size_t	len;
	int		type;
}t_word;

typedef struct s_tokens
{
	t_word	*words;
	size_t	size;
	t_env	**env;
}t_tokens;


/*****************************************************
 *						UTILS						 *
 *****************************************************/

	/*--------ENV--------*/

size_t	read_variable(char *or_env);
void	duplicate_env(char **env_cpy, char *or_env);
char	*cpy_or_env(char *or_env);
char	*ft_getenv(char *variable, char **env);
int		main(int argc, char **argv, char **envp);


/*****************************************************
 *					  COMMANDS						 *
 *****************************************************/


	/*--------PWD--------*/

void	pwd(void);

	/*--------ECHO-------*/

int		echo(char **args);

/*****************************************************
 *					  LEXER							 *
 *****************************************************/

	/*--------TOKENS_LEXER--------*/

bool	special_char(char corr);
size_t	get_char_special(char *token, char next_special_char);
char	get_next_char(char *token);
bool	search_char(char *token);

/*****************************************************
 *					  PARSER						 *
 *****************************************************/

	/*--------CHECK_ERRORS--------*/

int		is_rd(int c);
int		is_redirection(char *str, int i);
int		check_rd(char*str, int i);
int		check_input(char *str);

/*****************************************************
 *					  SIGNALS						 *
 *****************************************************/

void	signals(void);
void	signal_ctrl_c(int sig);

/*****************************************************
 *					  MAIN							 *
 *****************************************************/

int main();

/*****************************************************
 *					  PARSER						 *
 *****************************************************/

	/*--------TOKEN_MANAGER--------*/

t_tokens	*init_token(t_env **env);
int			add_words(t_tokens *tokens, char *str, size_t len, int type);
void		free_tokens(t_tokens *tokens);

	/*--------CHECK_ERRORS--------*/

int			is_rd(int c);
int			is_redirection(char *str, int i);
int			check_rd(char *str, int i);
int			check_input(char *str);

#endif
