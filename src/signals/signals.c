/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:21:33 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/08 19:46:20 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctrl_c(int sig)
{
	if (sig == SIGINT) //esto le indica que interrumpe el programa;
	{
		printf("\n");
		rl_on_new_line(); // esto indica que el cursor debe moverse a una nueva linea;
		rl_replace_line("", 1); // reemplaza el antiguo texto con uno nuevo
		rl_redisplay(); // muestra lo escrito por la funcion anterior.
	}
}

void	signal_ctrl_d(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrl_c);
}

