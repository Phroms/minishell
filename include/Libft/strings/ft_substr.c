/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:45:51 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/14 18:05:53 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*s_str;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (NULL);
	if (start + len > s_len)
		len = s_len - start;
	s_str = (char *)malloc((len + 1) * sizeof(char));
	if (!s_str)
		return (NULL);
	while (*s && start--)
		s++;
	i = 0;
	while (*s && i < len)
	{
		s_str[i] = *s;
		i++;
		s++;
	}
	s_str[i] = '\0';
	return (s_str);
}
/*int main()
{
	char dst[] = "";
	char *p;
	p = ft_substr(dst, 5, 3);
	printf("%s", p);
}*/
