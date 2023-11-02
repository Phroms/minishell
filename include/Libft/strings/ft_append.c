#include "libft.h"

/* Appends src to dst, frees dst and returns newly created string */
char  *ft_append(char **dst, char *src)
{
    char  *dst_tmp;
    char  *appendet;
    int    appendet_len;

    if (dst == NULL)
          dst_tmp = NULL;
    else
          dst_tmp = *dst;
    appendet_len = ft_strlen(dst_tmp) + ft_strlen(src);
    if (appendet_len == 0)
    {
        ft_free((void *)dst);
        return (NULL);
    }
    appendet = malloc((appendet_len + 1) * sizeof(*appendet));
    if (appendet == NULL)
        return (NULL);
    while (dst_tmp && *dst_tmp)
        *appendet++ = *dst_tmp++;
    while (src && *src)
        *appendet++ = *src++;
    *appendet = '\0';
    ft_free((void *)dst);
    return (appendet - appendet_len);
}
