/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:30:15 by agrimald          #+#    #+#             */
/*   Updated: 2023/10/24 21:49:54 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	lexer()
{
	/*
	 * Vas a guardar en una estructura el tipoo de textoo que te han pasa
	 * ej:   echo   hola   >   file.txt   |     ls      -la    <<   file_hrdc a | 
	 *       texto  texto  rd    texto    pipe  texto  texto   rd     texto
	 *
	 * RD -> << = HD  |  < = inFile  |  >> = append  |  > = outFile
	 * */
}


int	main(int ac, char **av, char *env[])
{
	while (1)
	{
		/*
		 * Estudiar que es la libreria READLINE
		 * */
		char *str;
		/*
		 * Guardar la linea leida en la str
		 * */
		lexer(str);
	}
}
