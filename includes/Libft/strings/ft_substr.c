/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:45:51 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/18 21:42:52 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptrs;
	size_t	i;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptrs = (char *) malloc(sizeof(char) * (len + 1));
	if (ptrs == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (i < len && s[i])
	{
		ptrs[i] = s[i + start];
		i++;
	}
	ptrs[i] = '\0';
	return (ptrs);
}
/*int main()
{
	char dst[] = "";
	char *p;
	p = ft_substr(dst, 5, 3);
	printf("%s", p);
}*/
