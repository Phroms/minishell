/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:28:47 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/08 18:36:29 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	int		i;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *) malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	free(s);
	return (dup);
}
/*int	main(int ac, char **av)
{
	char *mio;
	char *suyo;

	if(ac == 2)
	{
		mio = ft_strdup(av[1]);
		suyo = strdup(av[1]);
		printf("ADDR:%p:%s:\nADDR:%p:%s:\n",&mio, mio, &suyo, suyo);
	}
	return (0);
}*/
