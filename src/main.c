/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:57:55 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/07 18:39:40 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main()
{
	size_t	read_variable(char *or_env);
	void	duplicate_env(char **env_cpy, char *or_env);
	char	*cpy_or_env(char *or_env);
	char	*ft_getenv(char *variable, char **env);
	int		main(int argc, char **argv, char **envp);
	void	pwd(void);
	int		echo(char **args);
	bool	special_char(char corr);
	size_t	get_char_special(char *token, char next_special_char);
	char	get_next_char(char *token);
	bool	search_char(char *token);
	int		is_rd(int c);
	int		is_redirection(char *str, int i);
	int		check_rd(char*str, int i);
	int		check_input(char *str);
	void	signal_ctrlC(int sig);
	void	signal_ctrlD(void);
	return (0);
}
